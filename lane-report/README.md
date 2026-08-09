# The Lane Report

A board picker for Steamer Lane. Pulls current surf conditions (via Claude + web search), runs them through a decision engine encoding my quiver logic, and tells me which board to grab: Ghost, 6'6 Step-Up, Judah HP Egg (6'6, 37L), or Tiger XL (Pyzalien after the trade — there's a toggle).

## How it works

- **Frontend** (`src/App.jsx`): React + Vite. Conditions sliders (wave face, period, wind, crowd, session window), a live-pull button, and the recommendation card with reasoning.
- **Decision engine** (`decide()` in `App.jsx`): a pure function encoding the conditions-to-board table. Size bands, period ≥13s as the "punchy" threshold, wind-junk overrides, crowd/session-length tiebreakers, and a Nov–Mar winter-rubber bias. No ML, just the table — which means it's auditable and tunable.
- **Live conditions** (`api/conditions.js`): a serverless function that asks Claude (with the web search tool) to read the current Steamer Lane report and return strict JSON. The Anthropic API key lives server-side only.

## Why the proxy exists (read this before deploying)

The original version was built as a Claude artifact, where API calls are proxied and keyless. Outside that sandbox, calling `api.anthropic.com` from the browser would require shipping your API key to every visitor — anyone could open dev tools and drain your account. So the deployed version routes through `/api/conditions`, a Vercel serverless function that holds the key in an environment variable.

If you'd rather skip the API entirely, the app degrades gracefully: the live-pull button fails politely and everything works in manual mode. You can also later swap the proxy to hit Surfline's unofficial API directly (spot ID for Steamer Lane, `kbyg` endpoints) — cheaper per check, but unofficial and subject to breaking.

## Local development

```bash
npm install
npm run dev          # frontend only; live pull will fail without the proxy
```

To run the serverless function locally, use the Vercel CLI:

```bash
npm i -g vercel
echo "ANTHROPIC_API_KEY=sk-ant-..." > .env.local
vercel dev           # serves frontend + /api routes together
```

## Deploy (Vercel, ~5 minutes)

1. Push this repo to GitHub (see below).
2. Go to vercel.com → New Project → import the repo. Vercel auto-detects Vite; defaults are fine.
3. In Project Settings → Environment Variables, add `ANTHROPIC_API_KEY` with a key from console.anthropic.com. Scope it to Production (and Preview if you want).
4. Deploy. The `api/` directory is picked up automatically as serverless functions.
5. Open the URL on your phone, hit "Pull live conditions," and add it to your home screen.

Netlify works too (move `api/conditions.js` to `netlify/functions/` and adjust the fetch path). Vercel is the least-friction option for this structure.

## Push to GitHub

```bash
cd lane-report
git init
git add .
git commit -m "Lane Report: Steamer Lane board picker"
gh repo create lane-report --private --source=. --push
# or: create the repo on github.com, then
# git remote add origin git@github.com:<you>/lane-report.git
# git push -u origin main
```

## Cost note

Each live pull is one Sonnet call with web search — a few cents per check. Fine for personal dawn-patrol use; if you ever share the URL, add rate limiting to the proxy (Vercel KV or Upstash) so strangers can't run up your bill.

## Next steps / tuning backlog

- [ ] Deploy to Vercel, add to phone home screen
- [ ] Calibrate the "punchy" threshold (currently period ≥13s) against a few real sessions at the Lane
- [ ] Flip the quiver toggle default to Pyzalien after Aug 23 (San Diego trade)
- [ ] Optional: direct Surfline `kbyg` integration to skip the LLM call for raw numbers, keeping Claude only for the summary
- [ ] Optional: cache the live pull for 30 min (Vercel KV) so repeat checks are free
- [ ] Optional: add Pleasure Point as a second spot (the decision engine takes spot-agnostic inputs already — just needs a spot selector on the fetch prompt)
- [ ] Optional: session log — record what you actually rode and how it went, then tune `decide()` against your own data. You of all people know this is just an eval problem.

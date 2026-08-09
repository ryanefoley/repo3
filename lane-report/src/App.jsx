import { useState, useEffect } from "react";

/* ============================================================
   THE LANE REPORT — board picker for Ryan's quiver
   Palette: ink navy / seafoam paper / kelp / buoy orange / fog
   Type: Big Shoulders Display (display) / Archivo (body) / IBM Plex Mono (data)
   ============================================================ */

const C = {
  ink: "#0D1B24",
  inkSoft: "#162833",
  paper: "#EDF2EF",
  paperDim: "#DCE5E0",
  kelp: "#3E5C4B",
  kelpLight: "#5C7D6A",
  buoy: "#E8672B",
  fog: "#8FA5AC",
  fogDim: "#5E747C",
  white: "#F6FAF8",
};

/* ---------- Board definitions + SVG outlines ---------- */

const BOARDS = {
  egg: {
    name: "Judah HP Egg",
    dims: "6'6\" · 37L",
    tag: "Wave-count machine",
    outline: "M50 4 C30 14 22 50 22 95 C22 145 30 178 50 192 C70 178 78 145 78 95 C78 50 70 14 50 4 Z",
  },
  xl: {
    name: "Tiger XL",
    dims: "6'0\" · red",
    tag: "Soft-day shortboard",
    outline: "M50 6 C34 20 27 55 27 100 C27 150 33 178 44 190 L50 186 L56 190 C67 178 73 150 73 100 C73 55 66 20 50 6 Z",
  },
  pyzalien: {
    name: "Pyzalien",
    dims: "post-trade",
    tag: "Soft-day shortboard",
    outline: "M50 8 C33 20 26 55 27 100 C28 150 34 178 45 190 L50 185 L55 190 C66 178 72 150 73 100 C74 55 67 20 50 8 Z",
  },
  ghost: {
    name: "Ghost",
    dims: "daily driver",
    tag: "Good-wave weapon",
    outline: "M50 3 C37 18 30 55 30 100 C30 150 35 176 43 190 L50 184 L57 190 C65 176 70 150 70 100 C70 55 63 18 50 3 Z",
  },
  stepup: {
    name: "Step-Up",
    dims: "6'6\"",
    tag: "Paddle authority",
    outline: "M50 2 C39 16 33 55 33 100 C33 152 37 178 46 192 L50 187 L54 192 C63 178 67 152 67 100 C67 55 61 16 50 2 Z",
  },
  none: {
    name: "Coffee",
    dims: "stay dry",
    tag: "Not today",
    outline: "M32 60 L68 60 L64 150 C63 160 56 166 50 166 C44 166 37 160 36 150 Z M68 70 L78 70 C86 70 86 100 78 104 L66 106",
  },
};

/* ---------- Decision engine (the table, as code) ---------- */

function decide({ sizeFt, periodS, windMph, windType, crowd, sessionMin, month, postTrade }) {
  const soft = postTrade ? "pyzalien" : "xl";
  const winter = month >= 10 || month <= 2;
  const junk = (windType === "onshore" && windMph >= 14) || (windType === "cross" && windMph >= 18);
  const clean = windType === "offshore" || windType === "glassy" || windMph < 8;
  const punchy = periodS >= 13;
  const why = [];

  // Victory at sea
  if (junk && windMph >= 22) {
    if (sizeFt >= 8) {
      why.push("Big and blown out. No board fixes this — the ocean is closed.");
      return { first: "none", backup: null, why };
    }
    why.push("Victory-at-sea conditions. The egg's glide is the only thing that salvages texture like this.");
    return { first: "egg", backup: null, why };
  }

  // Overhead+
  if (sizeFt >= 8) {
    why.push("Solid and shifty — paddle authority and late-drop insurance win.");
    if (!clean) why.push("Some texture on it, so the extra foam under the chest matters even more.");
    return { first: "stepup", backup: "ghost", why };
  }

  // Head to overhead, decent or better
  if (sizeFt >= 6) {
    if (junk) {
      why.push("Head-high but junky. Wave count over performance — glide through the chop.");
      return { first: "egg", backup: soft, why };
    }
    why.push("The Lane doing its job. This is exactly what the Ghost is for.");
    if (punchy) why.push(`Long-period energy (${periodS}s) — real push, so the performance rocker pays off.`);
    return { first: "ghost", backup: "stepup", why };
  }

  // Chest to head
  if (sizeFt >= 4) {
    if (junk) {
      why.push("Wall-y but wind-affected. Take the paddle power and outglide the bump.");
      return { first: "egg", backup: soft, why };
    }
    if (punchy && clean) {
      why.push("Chest-to-head with clean faces and real energy — punchy enough for the Ghost.");
      return { first: "ghost", backup: soft, why };
    }
    if (crowd === "heavy" || sessionMin < 60) {
      why.push(sessionMin < 60 ? "Short window — maximize waves per minute." : "Packed lineup — paddle speed wins priority battles.");
      return { first: "egg", backup: soft, why };
    }
    why.push("Crumbly but wall-y and clean. Enough face to reward pocket surfing.");
    if (winter) why.push("Winter rubber tax noted — if you're feeling slow, grab the egg instead.");
    return { first: soft, backup: "egg", why };
  }

  // Waist to chest
  if (sizeFt >= 2.5) {
    if (crowd === "heavy" || !clean || sessionMin < 60 || winter) {
      const reasons = [];
      if (crowd === "heavy") reasons.push("crowd");
      if (!clean) reasons.push("texture");
      if (sessionMin < 60) reasons.push("short session");
      if (winter) reasons.push("winter rubber");
      why.push(`Small and soft with ${reasons.join(" + ")} in play — the egg converts liters directly into wave count.`);
      return { first: "egg", backup: soft, why };
    }
    why.push("Small but clean with a long window and room to move — enough wall to shortboard it.");
    return { first: soft, backup: "egg", why };
  }

  // Tiny
  why.push("Barely breaking. Only the egg makes this a session instead of a paddle.");
  return { first: "egg", backup: soft, why };
}

/* ---------- Live conditions via Claude + web search ---------- */

async function fetchConditions() {
  const prompt = `Search the web for the CURRENT surf report and forecast for Steamer Lane, Santa Cruz, California (Surfline, NOAA buoys, or similar). Today's conditions right now.

Respond with ONLY a raw JSON object, no markdown fences, no preamble, in exactly this shape:
{
  "waveMinFt": <number>,
  "waveMaxFt": <number>,
  "periodS": <number, dominant swell period seconds>,
  "windMph": <number>,
  "windType": "<one of: offshore | onshore | cross | glassy>",
  "tideFt": <number>,
  "tideDirection": "<rising | falling>",
  "summary": "<one sentence, plain words, max 20 words>"
}`;

  // In production this hits our own serverless proxy (see /api/conditions.js),
  // which holds the Anthropic API key server-side. Never call Anthropic
  // directly from the browser with a key — it would be visible to anyone.
  const res = await fetch("/api/conditions", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ prompt }),
  });
  if (!res.ok) throw new Error(`Proxy error ${res.status}`);
  const data = await res.json();
  const text = (data.content || [])
    .map((b) => (b.type === "text" ? b.text : ""))
    .filter(Boolean)
    .join("\n");
  const match = text.match(/\{[\s\S]*\}/);
  if (!match) throw new Error("No JSON in response");
  return JSON.parse(match[0]);
}

/* ---------- Small pieces ---------- */

function BoardCard({ id, role, active }) {
  const b = BOARDS[id];
  return (
    <div
      style={{
        display: "flex",
        alignItems: "center",
        gap: 18,
        padding: "18px 20px",
        background: active ? C.ink : "transparent",
        border: `1px solid ${active ? C.buoy : C.paperDim}`,
        borderRadius: 2,
      }}
    >
      <svg width="44" height="88" viewBox="0 0 100 196" style={{ flexShrink: 0 }}>
        <path
          d={b.outline}
          fill={active ? C.buoy : "none"}
          fillOpacity={active ? 0.14 : 0}
          stroke={active ? C.buoy : C.fogDim}
          strokeWidth="4"
          strokeLinejoin="round"
        />
        {id !== "none" && id !== "egg" && (
          <line x1="50" y1="10" x2="50" y2="186" stroke={active ? C.buoy : C.fogDim} strokeWidth="1.5" opacity="0.5" />
        )}
      </svg>
      <div>
        <div
          style={{
            fontFamily: "'IBM Plex Mono', monospace",
            fontSize: 10,
            letterSpacing: "0.18em",
            textTransform: "uppercase",
            color: active ? C.buoy : C.fogDim,
            marginBottom: 4,
          }}
        >
          {role}
        </div>
        <div
          style={{
            fontFamily: "'Big Shoulders Display', sans-serif",
            fontWeight: 700,
            fontSize: 26,
            lineHeight: 1,
            color: active ? C.white : C.ink,
            textTransform: "uppercase",
            letterSpacing: "0.02em",
          }}
        >
          {b.name}
        </div>
        <div style={{ fontFamily: "'Archivo', sans-serif", fontSize: 13, color: active ? C.fog : C.fogDim, marginTop: 3 }}>
          {b.dims} — {b.tag}
        </div>
      </div>
    </div>
  );
}

function Dial({ label, value, unit }) {
  return (
    <div style={{ borderLeft: `2px solid ${C.kelp}`, paddingLeft: 10 }}>
      <div
        style={{
          fontFamily: "'IBM Plex Mono', monospace",
          fontSize: 9,
          letterSpacing: "0.16em",
          textTransform: "uppercase",
          color: C.fogDim,
        }}
      >
        {label}
      </div>
      <div style={{ fontFamily: "'IBM Plex Mono', monospace", fontSize: 20, color: C.ink, marginTop: 2 }}>
        {value}
        <span style={{ fontSize: 11, color: C.fogDim, marginLeft: 3 }}>{unit}</span>
      </div>
    </div>
  );
}

function Seg({ options, value, onChange }) {
  return (
    <div style={{ display: "flex", border: `1px solid ${C.paperDim}`, borderRadius: 2, overflow: "hidden" }}>
      {options.map((o) => (
        <button
          key={o.v}
          onClick={() => onChange(o.v)}
          style={{
            flex: 1,
            padding: "8px 4px",
            fontFamily: "'IBM Plex Mono', monospace",
            fontSize: 10,
            letterSpacing: "0.08em",
            textTransform: "uppercase",
            border: "none",
            cursor: "pointer",
            background: value === o.v ? C.kelp : "transparent",
            color: value === o.v ? C.white : C.fogDim,
            transition: "background 0.15s",
          }}
        >
          {o.label}
        </button>
      ))}
    </div>
  );
}

function Slider({ label, value, onChange, min, max, step, fmt }) {
  return (
    <div>
      <div style={{ display: "flex", justifyContent: "space-between", marginBottom: 6 }}>
        <span
          style={{
            fontFamily: "'IBM Plex Mono', monospace",
            fontSize: 10,
            letterSpacing: "0.14em",
            textTransform: "uppercase",
            color: C.fogDim,
          }}
        >
          {label}
        </span>
        <span style={{ fontFamily: "'IBM Plex Mono', monospace", fontSize: 12, color: C.ink }}>{fmt(value)}</span>
      </div>
      <input
        type="range"
        min={min}
        max={max}
        step={step}
        value={value}
        onChange={(e) => onChange(Number(e.target.value))}
        style={{ width: "100%", accentColor: C.buoy }}
      />
    </div>
  );
}

/* ---------- App ---------- */

export default function App() {
  const [live, setLive] = useState(null);
  const [loading, setLoading] = useState(false);
  const [err, setErr] = useState(null);

  // manual / adjustable inputs
  const [sizeFt, setSizeFt] = useState(4);
  const [periodS, setPeriodS] = useState(11);
  const [windMph, setWindMph] = useState(6);
  const [windType, setWindType] = useState("glassy");
  const [crowd, setCrowd] = useState("medium");
  const [sessionMin, setSessionMin] = useState(90);
  const [postTrade, setPostTrade] = useState(false);

  const month = new Date().getMonth();

  async function pullReport() {
    setLoading(true);
    setErr(null);
    try {
      const r = await fetchConditions();
      setLive(r);
      setSizeFt((r.waveMinFt + r.waveMaxFt) / 2);
      setPeriodS(r.periodS);
      setWindMph(r.windMph);
      setWindType(r.windType);
    } catch (e) {
      setErr("Couldn't pull the live report — set conditions manually below.");
    }
    setLoading(false);
  }

  const rec = decide({ sizeFt, periodS, windMph, windType, crowd, sessionMin, month, postTrade });
  const first = BOARDS[rec.first];

  return (
    <div style={{ minHeight: "100vh", background: C.paper, fontFamily: "'Archivo', sans-serif" }}>
      <style>{`
        @import url('https://fonts.googleapis.com/css2?family=Big+Shoulders+Display:wght@600;700;800&family=Archivo:wght@400;500;600&family=IBM+Plex+Mono:wght@400;500&display=swap');
        * { box-sizing: border-box; margin: 0; }
        button:focus-visible, input:focus-visible { outline: 2px solid ${C.buoy}; outline-offset: 2px; }
        @media (prefers-reduced-motion: reduce) { * { transition: none !important; animation: none !important; } }
        @keyframes pulse { 0%,100% { opacity: 1 } 50% { opacity: 0.35 } }
      `}</style>

      {/* Header — buoy report masthead */}
      <header style={{ background: C.ink, padding: "26px 22px 22px", position: "relative", overflow: "hidden" }}>
        <svg
          viewBox="0 0 400 40"
          preserveAspectRatio="none"
          style={{ position: "absolute", bottom: -1, left: 0, width: "100%", height: 22 }}
        >
          <path d="M0 26 Q50 10 100 24 T200 22 T300 26 T400 20 L400 40 L0 40 Z" fill={C.paper} />
        </svg>
        <div
          style={{
            fontFamily: "'IBM Plex Mono', monospace",
            fontSize: 10,
            letterSpacing: "0.22em",
            color: C.buoy,
            textTransform: "uppercase",
          }}
        >
          36.9514°N · 122.0258°W · STN 46042 ADJ
        </div>
        <h1
          style={{
            fontFamily: "'Big Shoulders Display', sans-serif",
            fontWeight: 800,
            fontSize: "clamp(44px, 11vw, 72px)",
            lineHeight: 0.92,
            color: C.white,
            textTransform: "uppercase",
            marginTop: 8,
          }}
        >
          The Lane
          <br />
          <span style={{ color: C.buoy }}>Report</span>
        </h1>
        <div style={{ fontSize: 13, color: C.fog, marginTop: 10, maxWidth: 420, paddingBottom: 18 }}>
          Steamer Lane conditions → the right board out of your rack. Quiver logic, not vibes.
        </div>
      </header>

      <main style={{ maxWidth: 560, margin: "0 auto", padding: "20px 18px 60px" }}>
        {/* Live pull */}
        <button
          onClick={pullReport}
          disabled={loading}
          style={{
            width: "100%",
            padding: "16px",
            background: C.buoy,
            color: C.white,
            border: "none",
            borderRadius: 2,
            fontFamily: "'Big Shoulders Display', sans-serif",
            fontWeight: 700,
            fontSize: 22,
            letterSpacing: "0.06em",
            textTransform: "uppercase",
            cursor: loading ? "wait" : "pointer",
            animation: loading ? "pulse 1.2s infinite" : "none",
          }}
        >
          {loading ? "Reading the buoys…" : "Pull live conditions"}
        </button>

        {err && (
          <div
            style={{
              marginTop: 10,
              padding: "10px 12px",
              border: `1px solid ${C.buoy}`,
              borderRadius: 2,
              fontSize: 13,
              color: C.ink,
            }}
          >
            {err}
          </div>
        )}

        {live && (
          <div style={{ marginTop: 14, padding: "14px 16px", background: C.white, border: `1px solid ${C.paperDim}`, borderRadius: 2 }}>
            <div
              style={{
                fontFamily: "'IBM Plex Mono', monospace",
                fontSize: 10,
                letterSpacing: "0.16em",
                textTransform: "uppercase",
                color: C.kelp,
                marginBottom: 10,
              }}
            >
              Live · Steamer Lane
            </div>
            <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 14 }}>
              <Dial label="Surf" value={`${live.waveMinFt}–${live.waveMaxFt}`} unit="ft" />
              <Dial label="Period" value={live.periodS} unit="s" />
              <Dial label="Wind" value={`${live.windMph}`} unit={`mph ${live.windType}`} />
              <Dial label="Tide" value={live.tideFt} unit={`ft ${live.tideDirection}`} />
            </div>
            <div style={{ fontSize: 13, color: C.fogDim, marginTop: 12, fontStyle: "italic" }}>{live.summary}</div>
          </div>
        )}

        {/* The call */}
        <section style={{ marginTop: 26 }}>
          <div
            style={{
              fontFamily: "'IBM Plex Mono', monospace",
              fontSize: 10,
              letterSpacing: "0.2em",
              textTransform: "uppercase",
              color: C.fogDim,
              marginBottom: 10,
            }}
          >
            The call
          </div>
          <div style={{ display: "grid", gap: 10 }}>
            <BoardCard id={rec.first} role="First out of the rack" active />
            {rec.backup && <BoardCard id={rec.backup} role="Backup" active={false} />}
          </div>
          <div
            style={{
              marginTop: 12,
              padding: "14px 16px",
              borderLeft: `3px solid ${C.buoy}`,
              background: C.white,
              fontSize: 14,
              lineHeight: 1.55,
              color: C.ink,
            }}
          >
            {rec.why.map((w, i) => (
              <p key={i} style={{ marginTop: i ? 8 : 0 }}>
                {w}
              </p>
            ))}
          </div>
        </section>

        {/* Conditions controls */}
        <section style={{ marginTop: 30 }}>
          <div
            style={{
              fontFamily: "'IBM Plex Mono', monospace",
              fontSize: 10,
              letterSpacing: "0.2em",
              textTransform: "uppercase",
              color: C.fogDim,
              marginBottom: 14,
            }}
          >
            Conditions {live ? "· tweak the live read" : "· set manually"}
          </div>
          <div style={{ display: "grid", gap: 18 }}>
            <Slider label="Wave face" value={sizeFt} onChange={setSizeFt} min={1} max={15} step={0.5} fmt={(v) => `${v} ft`} />
            <Slider label="Swell period" value={periodS} onChange={setPeriodS} min={6} max={20} step={1} fmt={(v) => `${v} s`} />
            <Slider label="Wind speed" value={windMph} onChange={setWindMph} min={0} max={35} step={1} fmt={(v) => `${v} mph`} />
            <div>
              <div
                style={{
                  fontFamily: "'IBM Plex Mono', monospace",
                  fontSize: 10,
                  letterSpacing: "0.14em",
                  textTransform: "uppercase",
                  color: C.fogDim,
                  marginBottom: 6,
                }}
              >
                Wind direction
              </div>
              <Seg
                value={windType}
                onChange={setWindType}
                options={[
                  { v: "glassy", label: "Glassy" },
                  { v: "offshore", label: "Offshore" },
                  { v: "cross", label: "Cross" },
                  { v: "onshore", label: "Onshore" },
                ]}
              />
            </div>
            <div>
              <div
                style={{
                  fontFamily: "'IBM Plex Mono', monospace",
                  fontSize: 10,
                  letterSpacing: "0.14em",
                  textTransform: "uppercase",
                  color: C.fogDim,
                  marginBottom: 6,
                }}
              >
                Crowd
              </div>
              <Seg
                value={crowd}
                onChange={setCrowd}
                options={[
                  { v: "light", label: "Light" },
                  { v: "medium", label: "Medium" },
                  { v: "heavy", label: "Heavy" },
                ]}
              />
            </div>
            <Slider
              label="Session window"
              value={sessionMin}
              onChange={setSessionMin}
              min={30}
              max={180}
              step={15}
              fmt={(v) => (v < 60 ? `${v} min` : `${(v / 60).toFixed(v % 60 ? 1 : 0)} hr`)}
            />
            <div>
              <div
                style={{
                  fontFamily: "'IBM Plex Mono', monospace",
                  fontSize: 10,
                  letterSpacing: "0.14em",
                  textTransform: "uppercase",
                  color: C.fogDim,
                  marginBottom: 6,
                }}
              >
                Quiver era
              </div>
              <Seg
                value={postTrade ? "post" : "pre"}
                onChange={(v) => setPostTrade(v === "post")}
                options={[
                  { v: "pre", label: "Tiger XL (now)" },
                  { v: "post", label: "Pyzalien (post-trade)" },
                ]}
              />
            </div>
          </div>
        </section>

        <footer
          style={{
            marginTop: 40,
            paddingTop: 14,
            borderTop: `1px solid ${C.paperDim}`,
            fontFamily: "'IBM Plex Mono', monospace",
            fontSize: 10,
            letterSpacing: "0.12em",
            color: C.fogDim,
            textTransform: "uppercase",
          }}
        >
          Rack: Ghost · 6'6 Step-Up · Judah HP Egg · {postTrade ? "Pyzalien" : "Tiger XL"} — winter rubber tax applied Nov–Mar
        </footer>
      </main>
    </div>
  );
}

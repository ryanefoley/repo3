// Vercel serverless function: proxies the Steamer Lane conditions request
// to the Anthropic API. The API key lives in an environment variable
// (ANTHROPIC_API_KEY) and never reaches the browser.

export default async function handler(req, res) {
  if (req.method !== "POST") {
    return res.status(405).json({ error: "POST only" });
  }

  const { prompt } = req.body || {};
  if (!prompt || typeof prompt !== "string" || prompt.length > 4000) {
    return res.status(400).json({ error: "Bad prompt" });
  }

  try {
    const upstream = await fetch("https://api.anthropic.com/v1/messages", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        "x-api-key": process.env.ANTHROPIC_API_KEY,
        "anthropic-version": "2023-06-01",
      },
      body: JSON.stringify({
        model: "claude-sonnet-4-6",
        max_tokens: 1000,
        messages: [{ role: "user", content: prompt }],
        tools: [{ type: "web_search_20250305", name: "web_search" }],
      }),
    });

    const data = await upstream.json();
    if (!upstream.ok) {
      return res.status(upstream.status).json({ error: data?.error?.message || "Upstream error" });
    }
    return res.status(200).json(data);
  } catch (err) {
    return res.status(500).json({ error: "Proxy failure" });
  }
}

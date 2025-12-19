require('dotenv').config();
const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const OpenAI = require('openai');

const app = express();
app.use(cors());
app.use(bodyParser.json());

const openai = new OpenAI({ apiKey: process.env.OPENAI_API_KEY });

app.post('/api/chat', async (req, res) => {
  const { message, history = [] } = req.body;
  try {
    const completion = await openai.chat.completions.create({
      model: "gpt-4o",
      messages: [
        { role: 'system', content: "You are Jax, a supportive, nonjudgmental AI for men's mental health. Be conversational, warm, and never use clinical jargon." },
        ...history,
        { role: 'user', content: message }
      ],
      max_tokens: 200,
      temperature: 0.85,
    });
    res.json({ reply: completion.choices[0].message.content });
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: "AI failed to respond." });
  }
});


app.listen(3001, () => console.log('Forge AI backend running on http://localhost:3001'));


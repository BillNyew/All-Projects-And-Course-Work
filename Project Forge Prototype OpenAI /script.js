document.addEventListener('DOMContentLoaded', function() {
  // === CHAT MODAL LOGIC ===
  let jaxChatHistory = [];

  function startChat(initialMsg) {
    jaxChatHistory = []; // Reset chat history every time!
    const overlay = document.getElementById('chatOverlay');
    if (overlay) {
      overlay.style.display = 'flex';
      const chatBody = overlay.querySelector('.chat-body');
      if (chatBody) {
        chatBody.innerHTML = `<p>Hello! I'm <strong>Jax</strong>, your AI companion. What would you like to talk about today?</p>`;
        if (initialMsg) {
          chatBody.innerHTML += `<div class="user-msg"><strong>You:</strong> ${initialMsg}</div>`;
          jaxChatHistory.push({ role: 'user', content: initialMsg });
          chatBody.scrollTop = chatBody.scrollHeight;
          sendJaxReply(initialMsg, chatBody);
        }
      }
    }
  }
  function closeChat() {
    const overlay = document.getElementById('chatOverlay');
    if (overlay) overlay.style.display = 'none';
  }
  window.startChat = startChat;
  window.closeChat = closeChat;

  document.addEventListener('keydown', function(e) {
    if (e.key === "Escape") closeChat();
  });

  const closeBtn = document.getElementById('closeChatBtn');
  if (closeBtn) {
    closeBtn.onclick = closeChat;
  }

  async function fetchJaxReply(userMsg, chatHistory = []) {
    try {
      const res = await fetch('http://localhost:3001/api/chat', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ message: userMsg, history: chatHistory }),
      });
      const data = await res.json();
      return data.reply;
    } catch (e) {
      return "Sorry, I'm having trouble responding right now. Please try again later.";
    }
  }
  

  function sendUserMessage() {
    const chatOverlay = document.getElementById('chatOverlay');
    if (!chatOverlay) return;
    const chatInput = chatOverlay.querySelector('.chat-footer input');
    const chatBody = chatOverlay.querySelector('.chat-body');
    if (!chatInput || !chatBody) return;
    const msg = chatInput.value.trim();
    if (!msg) return;
    chatBody.innerHTML += `<div class="user-msg" style="margin-bottom:8px;"><strong>You:</strong> ${msg}</div>`;
    chatInput.value = '';
    chatBody.scrollTop = chatBody.scrollHeight;
    jaxChatHistory.push({ role: 'user', content: msg });

    // Show "Jax is typing..."
    chatBody.innerHTML += `<div class="jax-msg" style="margin-bottom:14px;" id="jax-typing"><strong>Jax:</strong> <em>typing…</em></div>`;
    chatBody.scrollTop = chatBody.scrollHeight;

    fetchJaxReply(msg, jaxChatHistory).then(response => {
      const typingDiv = chatBody.querySelector('#jax-typing');
      if (typingDiv) typingDiv.remove();
      chatBody.innerHTML += `<div class="jax-msg" style="margin-bottom:14px;"><strong>Jax:</strong> ${response}</div>`;
      chatBody.scrollTop = chatBody.scrollHeight;
      jaxChatHistory.push({ role: 'assistant', content: response });
    });
  }

  // Hook up input/button
  const chatOverlay = document.getElementById('chatOverlay');
  if (chatOverlay) {
    const chatInput = chatOverlay.querySelector('.chat-footer input');
    const chatButton = chatOverlay.querySelector('.chat-footer button');
    if (chatButton) chatButton.onclick = sendUserMessage;
    if (chatInput) {
      chatInput.addEventListener('keydown', function(e) {
        if (e.key === 'Enter') sendUserMessage();
      });
    }
  }

  // Only allow the "Start Talking to Jax" button to open chat
  const startJaxBtn = document.getElementById('startJaxChat');
  if (startJaxBtn) {
    startJaxBtn.addEventListener('click', function(e){
      e.preventDefault();
      startChat();
    });
  }

  // Optionally, statistic cards open chat
  const topicsGrids = document.querySelectorAll('.topics-grid');
  if (topicsGrids.length > 1) {
    topicsGrids[1].querySelectorAll('.topic-card').forEach(function(card){
      card.addEventListener('click', function(){
        startChat("I'd like to talk about " + card.textContent.trim());
      });
    });
  }

  // === HEAD CHECK (PROGRAMS PAGE) ===
  function renderSliderValues(id, min, max, value) {
    let out = '';
    for (let i = min; i <= max; i++) {
      out += `<span style="font-weight:${i==value?'700':'400'}">${i}</span>`;
    }
    const elem = document.getElementById(id + '-values');
    if (elem) elem.innerHTML = out;
  }

  function updateSliderValue(id) {
    const slider = document.getElementById(id);
    if (slider) renderSliderValues(id, parseInt(slider.min), parseInt(slider.max), parseInt(slider.value));
  }

  ['stress','anxiety','mood'].forEach(id => {
    const slider = document.getElementById(id);
    if (slider) {
      updateSliderValue(id);
      slider.addEventListener('input', () => updateSliderValue(id));
    }
  });

  // Handle head check form submission
  const headCheckForm = document.getElementById('head-check-form');
  if (headCheckForm) {
    headCheckForm.addEventListener('submit', function(e) {
      e.preventDefault();
      const s = +this.stress.value, a = +this.anxiety.value, m = +this.mood.value;
      const avg = ((s + a + (11 - m)) / 3).toFixed(1);
      let msg = '';
      if (avg <= 3) msg = 'You’re in a good head space. Keep up healthy routines.';
      else if (avg <= 6) msg = 'Mild concerns—consider chatting with the community or scheduling a therapist session.';
      else msg = 'Elevated risk. We recommend reaching out to a professional today.';
      const resultDiv = document.getElementById('head-check-result');
      if (resultDiv) resultDiv.innerText = msg;
    });
  }

  // === THERAPIST SEARCH (THERAPISTS PAGE) ===
  const therapistForm = document.getElementById('therapist-search-form');
  if (therapistForm) {
    therapistForm.addEventListener('submit', function(e) {
      e.preventDefault();
      const zip = this.zip.value.trim();
      document.getElementById('therapist-results').innerHTML =
        `<p>Showing results for ZIP code <strong>${zip}</strong>:</p>
         <ul>
           <li>Dr. Sarah Blake (PTSD) – Chat now</li>
           <li>Mark Rivera, LCSW (Veterans/Depression) – Video call at 5:00 PM</li>
           <li>Linda Chen, LPC (Trauma) – Video call at 2:00 PM</li>
         </ul>`;
    });
  }
});

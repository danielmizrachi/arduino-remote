function handleResponse(data) {
  if (data && data.states && data.states.length) {
    const { states } = data
    const buttons = document.querySelectorAll('[data-pin]')

    states.forEach((state, i) => {
      if (buttons[i]) {
        buttons[i].style.fontWeight = state ? 'bold' : 'normal'
      }
    });
  }
}

function toggle() {
  const pin = this.getAttribute('data-pin')

  fetch(`toggle/${pin}`)
    .then(res => res.json())
    .then(handleResponse)
    .catch(err => console.error(err))
}

const btn = document.querySelector('#sheepy');

/**
 * Another round of hot garbage here
 * This assigns a callback function on this event.
 */

const singleClickText = document.createElement('p');
const doubleClickText = document.createElement('p');

btn.onclick = function () {
    singleClickText.innerHTML = '<b>Meeeehheeee</b>';
}

btn.ondblclick = function () {
    doubleClickText.innerHTML = '<b>Muuuuuuh - wait what??</b>';
}

document.body.append(singleClickText);
document.body.append(doubleClickText);
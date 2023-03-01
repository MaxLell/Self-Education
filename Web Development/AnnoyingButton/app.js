/**
 * Select the button
 */

const btn = document.querySelector('button');

btn.addEventListener('mouseover', function () {
    console.log('you blood bastard moused me');

    /**
     * Not the ideal solution here for the manipulation
     * of the position, but at the moment the garbage will
     * do. Complexity Introduction only where that amount
     * of complexity is required.
     * 
     * Get a random value for x and y and teleport the button
     * to this location
     */
    const maxValueX = window.innerWidth;
    const maxValueY = window.innerHeight;
    const randomX = Math.floor(Math.random() * maxValueX);
    const randomY = Math.floor(Math.random() * maxValueY);
    btn.style.left = `${randomX}px`;
    btn.style.top = `${randomY}px`;
});

/**
 * Success - you actually managed to click the button
 * This is fairly easy. ... you just hit the tab key
 * and then you hit enter. Voila you hit the blinking
 * button
 */
btn.addEventListener('click', function () {
    btn.innerText = 'You got me';
    document.body.style.backgroundColor = 'green';
});
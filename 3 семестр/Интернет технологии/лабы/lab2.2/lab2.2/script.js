(function() {
"use strict"

let boolarr = [ true, false, false, false ];
const images = document.querySelectorAll('img');
images.forEach((el, i) => {
  var onMouseMove;
  let moveAtPosition;
  el.onmousedown = (event) => {
    if (boolarr[i] === true) {
      // ОБЪЯВЛЕНИЕ ФУНКЦИЙ
      moveAtPosition = (x, y) => {
        el.style.left = x - el.offsetWidth / 2 + 'px';
        el.style.top = y - el.offsetHeight / 2 + 'px';
      };

      onMouseMove = (event) => { moveAtPosition(event.pageX, event.pageY); };

      // СКРИПТ
      el.style.position = 'absolute';
      el.style.zIndex = 10;
      el.style.border = 2 + 'px solid red';
      moveAtPosition(event.pageX, event.pageY);

      document.addEventListener('mousemove', onMouseMove);
    }
    el.onmouseup = () => {
      document.removeEventListener('mousemove', onMouseMove);
      el.style.zIndex = 1;
      el.style.border = 0 + 'px';
      boolarr[i] = false;
      if (i === 3) {
        boolarr[0] = true;
      } else {
        boolarr[i + 1] = true;
      }
    }
  };

  el.ondragstart = () => { return false; };
});
}());

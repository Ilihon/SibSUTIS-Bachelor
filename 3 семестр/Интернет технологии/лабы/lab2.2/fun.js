
﻿document.onmousedown =
    function(e) {
  //событие срабатывает в момент нажатия на кнопку мыши
  var Element = e.target; //ссылка на объект для перемешения
  if (!Element.classList.contains('draggable'))
    return; // Если не нашли, клик вне draggable-объекта
  var coords, shiftX, shiftY;

  //Узнаем начальные координаты
  startDrag(e.clientX, e.clientY);

  //Перемещать по экрану
  document.onmousemove = function(e) { moveAt(e.clientX, e.clientY); };

  //Отследить окончание переноса
  Element.onmouseup = function() { finishDrag(); };
}
//Функции для перемещения:

//Начальные координаты
function startDrag(clientX, clientY) {
  shiftX = clientX - Element.getBoundingClientRect().left;
  //размер элемента и его позицию относительно окна легого
  shiftY = clientY - Element.getBoundingClientRect().top;

  Element.style.position = 'fixed'; //закрепляет позицию относительно окна

  document.body.appendChild(Element);

  moveAt(clientX, clientY);
};

//Конечные координаты
function finishDrag() {
  //Конец переноса, перейти от fixed к absolute-координатам
  Element.style.top = parseInt(Element.style.top) + pageYOffset + 'px';
  Element.style.position = 'absolute';

  document.onmousemove = null;
  Element.onmouseup = null;
}

//Передвинуть объект по координатам курсора
function moveAt(clientX, clientY) {
  // новые координаты
  var newX = clientX - shiftX;
  var newY = clientY - shiftY;
  Element.style.left = newX + 'px';
  Element.style.top = newY + 'px';
}

//Отменим действие по умолчанию на mousedown (выделение текста, оно лишнее)
return false;
}

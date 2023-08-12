const name = localStorage.getItem('name');
const color = localStorage.getItem('color');

if(!!!name){
    document.querySelector('.hello').textContent = 'Зарегистрируйтесь';
} else {
    var col = `${color}`;
    document.querySelector('.count').style.color = col;	
    document.querySelector('.hello').textContent = `Привет, ${name}`;
}

const count = localStorage.getItem('count');

if(!!!count) {
    document.querySelector('.count').textContent = 'Количество посещений страницы: 0';
    localStorage.setItem('count', `1`);
} else {
    document.querySelector('.count').textContent = `Количество посещений страницы: ${+count + 1}`;
    localStorage.setItem('count', `${+count + 1}`);
}

const time = localStorage.getItem('time');

if(!!!time) {
    document.querySelector('.time').textContent = 'Это первое посещение';
    localStorage.setItem('time', `${new Date().getTime()}`);
} else {
    const date = new Date();
    const date1 = new Date();
    date1.setTime(time);
    const now = date.getTime();

    const difTime = date.getTime() - date1.getTime();

    const difH = Math.floor(difTime / 1000 / 60 / 60);
    const difM = Math.floor(difTime / 1000 / 60) - difH * 60;
    const difS = Math.floor(difTime / 1000) - (difH * 60 + difM) * 60;

    document.querySelector('.time').textContent = `Вы были на этой странице: ${difH >= 1 ? difH : 0} часов, ${difM >= 1 ? difM : 0} минут, ${difS} секунд назад`;
    localStorage.setItem('time', `${now}`); 
}

const resetBtn = document.querySelector('.reset');
resetBtn.addEventListener('click', () => {
    localStorage.setItem('count', '0');
    document.querySelector('.count').textContent = 'Количество посещений страницы: 0';
});

function getRandomColor() {
  var letters = '012345';
  var color = letters[Math.floor(Math.random() * 6)];
  if(color == 0)
  	return "red";
  if(color == 1)
  	return "blue";
  if(color == 2)
  	return "green";
  if(color == 3)
  	return "yellow";
  if(color == 4)
  	return "orange";
  if(color == 5)
  	return "pink";
}

const regBtn = document.querySelector('.registration');
regBtn.addEventListener('click', () => {
    localStorage.setItem('color', getRandomColor());
    const name = document.querySelector('.name').value;
    if(!!name && name !== 'Dima') {
        localStorage.setItem('name', name);
        document.querySelector('.hello').textContent = `Привет, ${name}`;
    }
});


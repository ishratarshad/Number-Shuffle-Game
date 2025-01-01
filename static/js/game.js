let board = [];
let emptyTile = {};
let moves = 0;
let timerInterval;
let timer = 0;

function initGame(size) {
    clearInterval(timerInterval);
    moves = 0;
    timer = 0;
    document.getElementById('moves').textContent = moves;
    document.getElementById('timer').textContent = '00:00';

    timerInterval = setInterval(() => {
        timer++;
        const minutes = Math.floor(timer / 60).toString().padStart(2, '0');
        const seconds = (timer % 60).toString().padStart(2, '0');
        document.getElementById('timer').textContent = `${minutes}:${seconds}`;
    }, 1000);

    const numbers = [...Array(size * size - 1).keys()].map(n => n + 1);
    numbers.push(null);
    shuffleArray(numbers);

    board = [];
    for (let i = 0; i < size; i++) {
        board.push(numbers.slice(i * size, (i + 1) * size));
    }

    board.forEach((row, i) =>
        row.forEach((tile, j) => {
            if (tile === null) emptyTile = { row: i, col: j };
        })
    );

    drawBoard(size);
}

function drawBoard(size) {
    const gameBoard = document.getElementById('game-board');
    gameBoard.innerHTML = '';
    board.forEach((row, i) => {
        row.forEach((tile, j) => {
            const tileDiv = document.createElement('div');
            tileDiv.classList.add('tile');
            if (tile === null) {
                tileDiv.classList.add('empty');
            } else {
                tileDiv.textContent = tile;
            }
            gameBoard.appendChild(tileDiv);
        });
    });
}

function shuffleArray(array) {
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
}

document.addEventListener('keydown', (e) => {
    const size = parseInt(document.getElementById('game-board').dataset.size, 10);
    const { row, col } = emptyTile;
    let newRow = row,
        newCol = col;

    if (e.key === 'ArrowUp' && row < size - 1) newRow++;
    if (e.key === 'ArrowDown' && row > 0) newRow--;
    if (e.key === 'ArrowLeft' && col < size - 1) newCol++;
    if (e.key === 'ArrowRight' && col > 0) newCol--;

    if (newRow !== row || newCol !== col) {
        board[row][col] = board[newRow][newCol];
        board[newRow][newCol] = null;
        emptyTile = { row: newRow, col: newCol };
        moves++;
        document.getElementById('moves').textContent = moves;
        drawBoard(size);
    }
});

window.onload = () => {
    const size = parseInt(document.getElementById('game-board').dataset.size, 10);
    initGame(size);
};

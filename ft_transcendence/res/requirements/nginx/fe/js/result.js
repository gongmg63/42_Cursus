document.addEventListener('DOMContentLoaded', function() {

	// localStorage에 저장? url에 포함?
    const urlParams = new URLSearchParams(window.location.search);
    const result = urlParams.get('result'); // 'win' 또는 'lose'
    const avatarUrl = localStorage.getItem('userAvatar');
    const nickname = localStorage.getItem('userNickname');

    // 결과 메시지를 동적으로 업데이트
    const resultMessage = document.getElementById('resultMessage');
    if (result === 'win') {
        resultMessage.textContent = 'You Win!';
        resultMessage.classList.add('win'); // 승리 스타일 적용
    } else {
        resultMessage.textContent = 'You Lose!';
        resultMessage.classList.add('lose'); // 패배 스타일 적용
    }

    const userAvatar = document.getElementById('userAvatar');
    const userNickname = document.getElementById('userNickname');
    userAvatar.src = avatarUrl;
    userNickname.textContent = nickname;
});

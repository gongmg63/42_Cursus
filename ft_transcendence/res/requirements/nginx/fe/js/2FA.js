import { checkAndRefreshToken } from "./jwtRefresh.js";
import { render } from "./transcendence.js";

let is2FAEnabled;

// 상위 요소(body)에 이벤트 리스너를 등록하여 이벤트 위임 적용
document.body.addEventListener('click', function(event) {
	
    // Security modal을 열기 위한 버튼 클릭
    if (event.target && event.target.matches('.security-btn')) {
        const securityModal = document.getElementById('securityModal');
        const confirm2faBtn = document.getElementById('confirm2faBtn');
        const cancel2faBtn = document.getElementById('cancel2faBtn');
        const closeBtns = document.querySelectorAll('.close');

        securityModal.style.display = 'block';
        confirm2faBtn.style.display = 'block';
        cancel2faBtn.style.display = 'block';
        closeBtns.forEach(btn => {
            btn.style.display = 'block';
        });
        update2FAStatus();
    }

    // Modal 닫기 버튼 클릭
    if (event.target && event.target.matches('.close')) {
        const securityModal = document.getElementById('securityModal');
        const change2faModal = document.getElementById('change2faModal');
        securityModal.style.display = 'none';
        change2faModal.style.display = 'none';
    }

    // 2FA 변경 버튼 클릭
    if (event.target && event.target.matches('#changeSettingsBtn')) {
        const securityModal = document.getElementById('securityModal');
        const change2faModal = document.getElementById('change2faModal');
        const changeTitle = document.getElementById('2faChangeTitle');
        const qrCodeContainer = document.getElementById('qrCodeContainer');
        const nextStepBtn = document.getElementById('nextStepBtn');

        securityModal.style.display = 'none';
        change2faModal.style.display = 'block';

        if (is2FAEnabled) {
            changeTitle.textContent = '2FA 설정을 해제하시겠습니까?';
            qrCodeContainer.style.display = 'none';
            nextStepBtn.style.display = 'none';
        } else {
            changeTitle.textContent = '2FA 설정을 하시겠습니까?';
        }
    }

    // 2FA 설정 확인 버튼 클릭
    if (event.target && event.target.matches('#confirm2faBtn')) {
        if (is2FAEnabled) {
            disable2FA();
        } else {
            enable2FA();
        }
    }

    // 2FA 설정 취소 버튼 클릭
    if (event.target && event.target.matches('#cancel2faBtn')) {
        const change2faModal = document.getElementById('change2faModal');
        change2faModal.style.display = 'none';
    }

    if (event.target && event.target.matches('#nextStepBtn')) {
        const nickname = localStorage.getItem("nickname");
		render(`#/authentication?nickname=${nickname}`);
    }
});

export function setTFA(tfa)
{
	is2FAEnabled = tfa;
}

function update2FAStatus() {
    const statusMessage = document.getElementById('2faStatusMessage');

	console.log("is2FAEnabled: ", is2FAEnabled);
	if (is2FAEnabled)
		statusMessage.textContent = '2FA가 활성화된 상태입니다.';
	else
		statusMessage.textContent = '현재 2FA가 비활성화되어 있습니다.';
}

function enable2FA() {
    is2FAEnabled = true; // 2FA 활성화
    const qrCodeContainer = document.getElementById('qrCodeContainer');
    const nextStepBtn = document.getElementById('nextStepBtn');
    const confirm2faBtn = document.getElementById('confirm2faBtn');
    const cancel2faBtn = document.getElementById('cancel2faBtn');
    const closeBtns = document.querySelectorAll('.close');

    checkAndRefreshToken().then(() => {
        const access_token = localStorage.getItem("access_token");
        fetch('/api/user/enable', {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${access_token}`,
                'Content-Type': 'application/json'
            }
        })
        .then(response => {
            if (response.status == 404) throw new Error('User data not found (404)');
            if (response.status == 500) throw new Error('Server error (500)');
            if (!response.ok) throw new Error(`Unexpected error: ${response.status}`);
            return response.json();
        })
        .then(data => {
            const qrCodeImage = document.getElementById('qrCodeImage');
            qrCodeImage.src = `data:image/png;base64,${data.qr_code_url}`;

            qrCodeContainer.style.display = 'block';
            nextStepBtn.style.display = 'block';
            confirm2faBtn.style.display = 'none';
            cancel2faBtn.style.display = 'none';
            closeBtns.forEach(btn => btn.style.display = 'none');
            update2FAStatus();
        })
        .catch(error => {
            console.error('Error fetching user data: ', error);
            handleError(error);
        });
    });
}

// 2FA 비활성화 함수
function disable2FA() {
    is2FAEnabled = false; // 2FA 비활성화
    checkAndRefreshToken().then(() => {
        const access_token = localStorage.getItem("access_token");
        fetch('/api/user/disable', {
            method: 'GET',
            headers: {
                'Authorization': `Bearer ${access_token}`
            }
        })
        .then(response => {
            if (response.status == 404) throw new Error('User data not found (404)');
            if (response.status == 500) throw new Error('Server error (500)');
            if (!response.ok) throw new Error(`Unexpected error: ${response.status}`);
            return response.json();
        })
        .then(data => {
            alert('2FA가 비활성화되었습니다.');
			const securityModal = document.getElementById('securityModal');
			const change2faModal = document.getElementById('change2faModal');
			securityModal.style.display = 'none';
			change2faModal.style.display = 'none';
            update2FAStatus();
        })
        .catch(error => {
            console.error('Error fetching user data: ', error);
            handleError(error);
        });
    });
}
let is2FAEnabled = false; // 예시로 2FA 설정 여부를 저장하는 변수. 서버에서 실제 상태를 받아올 수 있음.

const securityBtn = document.querySelector('.security-btn');
const securityModal = document.getElementById('securityModal');
const change2faModal = document.getElementById('change2faModal');
const closeBtns = document.querySelectorAll('.close');
const changeSettingsBtn = document.getElementById('changeSettingsBtn');
const confirm2faBtn = document.getElementById('confirm2faBtn');
const cancel2faBtn = document.getElementById('cancel2faBtn');

securityBtn.addEventListener('click', () => {
    securityModal.style.display = 'block';
    update2FAStatus();
});

closeBtns.forEach(btn => {
    btn.addEventListener('click', () => {
        securityModal.style.display = 'none';
        change2faModal.style.display = 'none';
    });
});

document.getElementById('nextStepBtn').addEventListener('click', function() {
    window.location.href = '/2fa/authentication.html';
});

function update2FAStatus() {
    const statusMessage = document.getElementById('2faStatusMessage');

	if (is2FAEnabled)
		statusMessage.textContent = '2FA가 활성화된 상태입니다.';
	else
		statusMessage.textContent = '현재 2FA가 비활성화되어 있습니다.';
}

changeSettingsBtn.addEventListener('click', () => {
	securityModal.style.display = 'none';
	change2faModal.style.display = 'block';

	const changeTitle = document.getElementById('2faChangeTitle');
	if (is2FAEnabled)
		changeTitle.textContent = '2FA 설정을 해제하시겠습니까?';
	else
		changeTitle.textContent = '2FA 설정을 하시겠습니까?';
});

confirm2faBtn.addEventListener('click', () => {
	if (is2FAEnabled)
		disable2FA();
	else
		enable2FA();
	change2faModal.style.display = 'none';
});

cancel2faBtn.addEventListener('click', () => {
    change2faModal.style.display = 'none';
});

function enable2FA() {
    is2FAEnabled = true; // 2FA 활성화
    alert('2FA가 활성화되었습니다.');
    update2FAStatus();

	// //#region QR fetch API
	// const access_token = localStorage.getItem("access_token");
	// // 서버로부터 QR Code GET
	// fetch('/api/user/2fa/enable', {
	// 	method: 'GET',
	// 	headers: {
	// 		'Authorization': `Bearer ${access_token}`,
	// 		'Content-Type': 'application/json'
	// 	},
	// })
	// .then(response => {
	// 	if (response.status == 404)
	// 		throw new Error('User data not found (404)');
	// 	else if (response.status == 500)
	// 		throw new Error('Server error (500)')
	// 	else if (!response.ok)
	// 		throw new Error(`Unexpected error: ${response.status}`);
	// 	return response.json();
	// })
	// .then(data => {
    //     const qrCodeImage = document.getElementById('qrCodeImage');
    //     qrCodeImage.src = data.qr_code_url;  // 서버가 제공한 QR 코드 URL - 추후 수정 가능.

    //     const qrCodeContainer = document.getElementById('qrCodeContainer');
	// 	const nextStepBtn = document.getElementById('nextStepBtn');
    //     qrCodeContainer.style.display = 'block';
	// 	nextStepBtn.style.display = 'block';
	//  update2FAStatus();
	// })
	// .catch(error => {
	// 	console.error('Error fetching user data: ', error);
	// 	handleError(error);
	// });
	// //#endregion
}

function disable2FA() {
    is2FAEnabled = false; // 2FA 비활성화
    alert('2FA가 비활성화되었습니다.');
    update2FAStatus();

	// //#region QR disable fetch API
	// const access_token = localStorage.getItem("access_token");
	// // 서버에게 disable 요청.
	// fetch('/api/user/2fa/disable', {
	// 	method: 'GET',
	// 	headers: {
	// 		'Authorization': `Bearer ${access_token}`,
	// 		'Content-Type': 'application/json'
	// 	},
	// })
	// .then(response => {
	// 	if (response.status == 404)
	// 		throw new Error('User data not found (404)');
	// 	else if (response.status == 500)
	// 		throw new Error('Server error (500)')
	// 	else if (!response.ok)
	// 		throw new Error(`Unexpected error: ${response.status}`);
	// 	return response.json();
	// })
	// .then(data => {
    // 	alert('2FA가 비활성화되었습니다.');
    //     update2FAStatus();
	// })
	// .catch(error => {
	// 	console.error('Error fetching user data: ', error);
	// 	handleError(error);
	// });
	// //#endregion
}

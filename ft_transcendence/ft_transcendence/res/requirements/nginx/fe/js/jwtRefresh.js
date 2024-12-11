export function isTokenExpired(token) {
    if (!token) return true;
    const payload = JSON.parse(atob(token.split('.')[1]));
    const expirationTime = payload.exp * 1000; // 만료 시간을 밀리초로 변환
    return Date.now() >= expirationTime; // 현재 시간이 만료 시간 이후인지 검사
}

export function refreshToken() {
    return new Promise((resolve, reject) => {
        const refreshToken = localStorage.getItem('refresh_token'); // 저장된 refresh token 가져오기
        if (!refreshToken) {
            reject(new Error('Token is not exist'));
            return; // 함수 종료
        }

        fetch('/api/user/token/refresh/', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${refreshToken}`,
            },
            body: JSON.stringify({ refresh: refreshToken }),
        })
        .then(response => {
            if (!response.ok) {
                reject(new Error('Failed to refresh token'));
                return; // reject 후 함수 종료
            }
            
            return response.json(); // 프로미스 체인을 계속 이어가기 위해 return
        })
        .then(data => {
            // 새로운 access token과 refresh token 저장
            localStorage.setItem('access_token', data.access);
            localStorage.setItem('refresh_token', data.refresh);
            resolve(); // 토큰 갱신 성공 시 resolve
        })
        .catch(error => {
            console.error('Error:', error.message);
            reject(error); // 오류 발생 시 reject
        });
    });
}
export function verifyToken() {
    return new Promise((resolve, reject) => {
        const accessToken = localStorage.getItem('access_token'); // 저장된 access token 가져오기
        if (!accessToken) {
            reject(new Error('Token is not exist'));
            return; // 함수 종료
        }

        fetch('/api/user/token/verify/', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ 'token': accessToken }),
        })
        .then(response => {
            if (!response.ok) {
                reject(new Error('Failed to refresh token'));
                return; // reject 후 함수 종료
            }
            resolve();
            return ;
        })
        .catch(error => {
            console.error('Error:', error.message);
            reject(error); // 오류 발생 시 reject
        });
    });
}

export function checkAndRefreshToken() {
    return new Promise((resolve, reject) => {
        const accessToken = localStorage.getItem('access_token');

        verifyToken()
        .then(() => {
            resolve();
        })
        .catch(error => {
            if (isTokenExpired(accessToken)) {
                refreshToken()
                .then(() => {
                    resolve();
                })
                .catch(error => {
                    console.error(error.message);
                    reject(error);
                });
            } else {
                resolve();
            }
        });
    });
}
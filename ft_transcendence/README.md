# ft_transcendence
> 실시간 멀티 플레이 핑퐁 게임이 가능한 웹 사이트 만들기

![Django](https://img.shields.io/badge/django-%23092E20.svg?style=for-the-badge&logo=django&logoColor=white)
![Socket.io](https://img.shields.io/badge/Socket.io-black?style=for-the-badge&logo=socket.io&badgeColor=010101)
![JavaScript](https://img.shields.io/badge/javascript-%23323330.svg?style=for-the-badge&logo=javascript&logoColor=%23F7DF1E)
![Postgres](https://img.shields.io/badge/postgres-%23316192.svg?style=for-the-badge&logo=postgresql&logoColor=white)
![Nginx](https://img.shields.io/badge/nginx-%23009639.svg?style=for-the-badge&logo=nginx&logoColor=white)
![Docker](https://img.shields.io/badge/docker-%230db7ed.svg?style=for-the-badge&logo=docker&logoColor=white)
![ElasticSearch](https://img.shields.io/badge/-ElasticSearch-005571?style=for-the-badge&logo=elasticsearch)

---

# 👍프로젝트 팀원
- Mkong : 백엔드
- Jgoo : 프론트 엔드
- Yakim : 백엔드, DevOps

---

# ⚙️실행방법
```bash
make #https://127.0.0.1 로 접속 가능
```

> OAuth Login

![로그인 영상](../assets/transcendence_login.gif)

> Game

![게임 영상](../assets/transcendence_game.gif)

> Profile

![프로필](../assets/transcendence_profile.png)

> 

# 🚀Project Layout
- `res`
    - `requirements`
		- `django`
			- 백엔드 서버 이미지
		- `elasticsearch`, `filebeat`, `kibana`, `setup`
			- 로그 저장을 위한 elk이미지
		- `nginx`
			- 프론트 엔드 이미지
		- `postgresql`
			- 데이터베이스 이미지

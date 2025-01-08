# Inception
- 이 프로젝트는 `Docker`를 활용하여 `WordPress`, `NGINX`, `MariaDB`와 같은 서비스를 포함하는 가상화된 시스템 인프라를 구축하는 시스템 관리 프로젝트입니다.
---
# ⚠️프로젝트 요구사항
- 이 프로젝트는 특정 규칙에 따라 여러 서비스로 구성된 소규모 인프라를 설정하는 작업을 포함합니다. 모든 작업은 가상 머신에서 수행해야 하며, docker-compose를 사용해야 합니다.
- 필수 조건:
    1. 각 Docker 이미지의 이름은 해당 서비스 이름과 동일해야 합니다.
    2. 각 서비스는 전용 컨테이너에서 실행되어야 합니다.
    3. 성능상의 이유로, 컨테이너는 Alpine 또는 Debian의 최신 안정화 버전 중 하나를 기반으로 만들어야 합니다.
    4. 각 서비스마다 개별 Dockerfile을 작성해야 하며, Dockerfile은 docker-compose.yml에서 호출되어야 합니다.
        - 이미 만들어진 Docker 이미지를 다운로드하거나 DockerHub에서 가져오는 것은 금지입니다.
        - 단, Alpine/Debian 이미지는 예외입니다.
- 구성요소
    - NGINX: TLSv1.2 또는 TLSv1.3만을 지원하는 컨테이너.
    - WordPress + php-fpm: NGINX 없이 설치 및 설정.
    - MariaDB: NGINX 없이 설치.
    - 두 개의 볼륨:
        - WordPress 데이터베이스 저장용.
        - WordPress 웹사이트 파일 저장용.
    - Docker 네트워크: 컨테이너 간 연결을 담당.
---

# ⚙️실행방법
```bash
make
```

# 🚀Project Layout
- `set_dck.sh`
    - 가상머신에서 처음 `Docker`, `Docker compose` 세팅을 위한 스크립트 

- `srcs`
    - `requirements`
        - `mariadb`
            - `mariadb` 이미지 생성을 위한 config, 초기 DB 생성 스크립트와 **Dokcerfile** 
        - `nginx`
            - `nginx` 이미지 생성을 위한 config와 **Dockerfile**
        - `wordpress`
            - `wordpress`이미지 생성을 위한 config, 초기 wordpress 세팅 스크립트와 **Dockerfile** 
    - `docker-compose.yml`
        -   `mariadb`, `nginx`, `wordpress` 컨테이너를 생성과 옵션 및 환경을 정의하기 위한 도구.
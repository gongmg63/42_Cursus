ARG STACK_VERSION

FROM docker.elastic.co/elasticsearch/elasticsearch:${STACK_VERSION}

COPY init.sh ./init.sh
COPY export.ndjson ./export.ndjson

ENTRYPOINT ["./init.sh"]

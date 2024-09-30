FROM golang AS development

WORKDIR /snippetbox/web

COPY /snippetbox/ /snippetbox

RUN go mod init go-web
RUN go mod tidy
RUN go build -o /go-webserver


FROM debian AS builder

WORKDIR /

COPY --from=development /go-webserver /go-webserver
COPY /snippetbox/ui /ui
COPY cmd.sh /

EXPOSE 8888

CMD ["/cmd.sh"]

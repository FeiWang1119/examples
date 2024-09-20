FROM golang

WORKDIR /snippetbox/web
COPY /snippetbox/ /snippetbox
COPY cmd.sh /
RUN go mod init go-web
RUN go build -o ./go-webserver

EXPOSE 8888

CMD ["/cmd.sh"]

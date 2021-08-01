FROM gcc:latest
COPY . /usr/src/code
WORKDIR /usr/src/code
RUN make
CMD ["./run"]
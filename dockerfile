FROM ubuntu:latest as build
RUN apt-get -y update && apt-get install -y
RUN apt-get -y install clang
COPY . /usr/src/solution
WORKDIR /usr/src/solution
RUN ./build.sh

FROM ubuntu:latest
COPY --from=build ./usr/src/solution/release/ ./release/
WORKDIR ./release
ENTRYPOINT ["./run.sh"]
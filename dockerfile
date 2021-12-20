FROM ubuntu:latest as build
RUN apt-get -y update && apt-get install -y
RUN apt-get -y install clang
COPY . /usr/src/solution
WORKDIR /usr/src/solution
RUN chmod +x ./build.sh
RUN ./build.sh

FROM ubuntu:latest
COPY --from=build ./usr/src/solution/release/ ./release/
WORKDIR ./release
RUN chmod +x ./run.sh
ENTRYPOINT ["./run.sh"]
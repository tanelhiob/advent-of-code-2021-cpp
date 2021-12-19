FROM ubuntu:latest as build
RUN apt-get -y update && apt-get install -y
RUN apt-get -y install clang
COPY . /usr/src/solution
WORKDIR /usr/src/solution
RUN clang++ -O3 -o ./01/program01 ./01/main.cpp

FROM ubuntu:latest
COPY --from=build ./usr/src/solution/01/program01 ./01/
COPY --from=build ./usr/src/solution/01/input.txt ./01/
WORKDIR ./01/
ENTRYPOINT ["./program01"]
#FROM conanio/clang9-x86 AS build
#FROM conanio/gcc49-x86 AS build
FROM conanio/clang9 AS build

#COPY conan-profile-linux /home/conan/.conan/profiles/default

# Launch conan install first to be able to use docker cache
#COPY conanfile.txt .
#RUN mkdir build
# use --build=missing to compile missing dependencies
#RUN conan install --build=missing . -if build/
#RUN conan install . -if build/

#RUN sudo apt-get update -y && sudo apt-get install -y libcurl4
RUN sudo apt-get update -y && sudo apt-get install -y libcurl4-openssl-dev libboost-all-dev
#libboost-all-dev

COPY . .

# Compile with cmake
# -Wno-c++11-narrowing to avoid error with restinio
# -static to be used with minimalist docker image
# -DCMAKE_EXE_LINKER_FLAGS=
#RUN cmake -DCMAKE_CXX_FLAGS="-pthread -Wno-c++11-narrowing" . -B build/
RUN cmake -DCMAKE_CXX_FLAGS="-pthread" . -B build/
#RUN cmake . -B build/
RUN cmake --build build/

#FROM conanio/clang9
FROM ubuntu
#FROM alpine
#FROM scratch

#RUN apk update && apk add --no-cache musl-dev
RUN apt-get update -y && apt-get install -y curl

COPY --from=build /home/conan/build/src/bin/crawler_rest /usr/local/bin
COPY --from=build /home/conan/build/src/bin/crawler_cli /usr/local/bin

#COPY etc/conf.ini /etc/http-server/conf.ini
COPY entrypoint.sh /usr/local/bin

ENTRYPOINT ["/usr/local/bin/entrypoint.sh", "/usr/local/bin/crawler_rest"]

#CMD ["-t", "/var/www", "--host", "0.0.0.0"]
#ENTRYPOINT ["/usr/local/bin/crawler_rest"]

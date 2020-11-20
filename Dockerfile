#FROM conanio/clang9-x86 AS build
#FROM conanio/gcc49-x86 AS build
#FROM conanio/clang9 AS build
FROM ubuntu:focal AS build

#COPY conan-profile-linux /home/conan/.conan/profiles/default

# Launch conan install first to be able to use docker cache
#COPY conanfile.txt .
#RUN mkdir build
# use --build=missing to compile missing dependencies
#RUN conan install --build=missing . -if build/
#RUN conan install . -if build/

#RUN echo "deb http://ppa.launchpad.net/mhier/libboost-latest/ubuntu bionic main"  | sudo tee -a /etc/apt/sources.list
#RUN echo "deb-src http://ppa.launchpad.net/mhier/libboost-latest/ubuntu bionic main"  | sudo tee -a /etc/apt/sources.list

#RUN ln -s /usr/bin/python3.8.2 /usr/bin/python3

ENV DEBIAN_FRONTEND='noninteractive'

RUN apt-get update -y
RUN apt-get install -y clang cmake git
#RUN apt-get install -y software-properties-common
#RUN add-apt-repository ppa:boost-latest/ppa
#RUN add-apt-repository ppa:mhier/libboost-latest

#RUN sudo apt-get update -y && sudo apt-get install -y libcurl4-openssl-dev
RUN apt-get update -y && apt install -y libboost-all-dev libssl-dev
# libboost-all-dev
# libssl-dev
# libcurl4-openssl-dev

#RUN cd /home && wget https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz \
#  && tar xfz boost_1_74_0.tar.gz \
#  && rm boost_1_74_0.tar.gz \
#  && cd boost_1_74_0 \
#  && ./bootstrap.sh --prefix=/usr/local \
#  && ./b2 install \
#  && cd /home \
#  && rm -rf boost_1_74_0

COPY . .

#RUN export CC=/usr/bin/clang-9
#RUN export CXX=/usr/bin/clang++-9
#ENV CMAKE_CXX_FLAGS="-lstdc++ -std=c++11 -pthread"

# Compile with cmake
# -Wno-c++11-narrowing to avoid error with restinio
# -static to be used with minimalist docker image
# -DCMAKE_EXE_LINKER_FLAGS=
#RUN cmake -DCMAKE_CXX_FLAGS="-pthread -Wno-c++11-narrowing" . -B build/
#RUN cmake -DCMAKE_CXX_FLAGS="-std=c++11 -pthread" . -B build/
RUN cmake -DCMAKE_CXX_FLAGS="-pthread" . -B build/
#RUN cmake -DCMAKE_C_COMPILER="/usr/bin/clang" -DCMAKE_CXX_COMPILER="/usr/bin/clang++" -DCMAKE_CXX_FLAGS="-pthread" . -B build/
#RUN cmake --build build/
#RUN ./clean-build.sh

#FROM conanio/clang9
FROM ubuntu
#FROM alpine
#FROM scratch

#RUN apk update && apk add --no-cache musl-dev
#RUN apt-get update -y && apt-get install -y curl
#RUN apt-get update -y && apt-get install -y openssl ca-certificates

COPY --from=build /build/src/bin/crawler_rest /usr/local/bin
COPY --from=build /build/src/bin/crawler_cli /usr/local/bin

#COPY etc/conf.ini /etc/http-server/conf.ini
COPY entrypoint.sh /usr/local/bin

#ENTRYPOINT ["/usr/local/bin/entrypoint.sh", "/usr/local/bin/crawler_rest"]

#CMD ["-t", "/var/www", "--host", "0.0.0.0"]
#ENTRYPOINT ["/usr/local/bin/crawler_rest"]

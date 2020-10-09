#FROM conanio/clang9-x86 AS build
#FROM conanio/gcc49-x86 AS build
FROM conanio/clang9 AS build

#COPY conan-profile-linux /home/conan/.conan/profiles/default

# Launch conan install first to be able to use docker cache
COPY conanfile.txt .
RUN mkdir build
# use --build=missing to compile missing dependencies
#RUN conan install --build=missing . -if build/
RUN conan install . -if build/

COPY . .

# Compile with cmake
# -Wno-c++11-narrowing to avoid error with restinio
# -static to be used with minimalist docker image
#RUN cmake -DCMAKE_CXX_FLAGS="-Wno-c++11-narrowing -static" . -B build/
RUN cmake -DCMAKE_CXX_FLAGS="-static" . -B build/
RUN cmake --build build/


FROM alpine
#FROM scratch

COPY --from=build /home/conan/build/bin/crawler ./
ENTRYPOINT ["./crawler"]

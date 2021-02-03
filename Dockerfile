FROM ubuntu:bionic AS build

RUN apt-get update && \
	apt-get install -y build-essential make libncurses5-dev

WORKDIR /app

COPY . .

RUN make

FROM ubuntu:bionic

WORKDIR /app

COPY --from=build /app /app

CMD ["/app/bin/ascii"]
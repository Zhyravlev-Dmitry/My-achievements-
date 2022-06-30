FROM gcc as gcc_
RUN apt-get update
RUN apt-get -y install cmake

COPY . /opt/techprog/
WORKDIR /opt/techprog
RUN mkdir build
WORKDIR /opt/techprog/build
RUN cmake ..
RUN make
WORKDIR /

FROM python:3
COPY --from=gcc_ /opt/techprog /opt/techprog

RUN pip install flask
EXPOSE 8898

RUN groupadd -r tp2022user
RUN useradd -rg tp2022user tp2022user
USER tp2022user

WORKDIR /opt/techprog/
ENV FLASK_RUN_HOST=0.0.0.0
ENV FLASK_RUN_PORT=8898
ENV FLASK_APP=app.py
CMD ["flask", "run"]

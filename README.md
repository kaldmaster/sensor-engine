# To get it to run

Due to issues with a few packages not being updated, a few manual corrections needs to be made. 

In *AsyncWebSocket* package, the compiler will complain about an ambigous IPAdress constructor call. It is fixed by following this https://github.com/me-no-dev/ESPAsyncWebServer/pull/970.

In *ESPAsyncWebServer* this fix needs then to be applied https://github.com/me-no-dev/ESPAsyncWebServer/issues/1085#issuecomment-1009310343.

## SignalK server in docker for testing
docker run -d --init  --name signalk-server -p 3000:3000 -v ${pwd}:/home/node/.signalk signalk/signalk-server

import http from 'node:http';

const TOTAL_REQUESTS = 1000;
const CONCURRENCY = 100;
const TARGET_URL = "http://localhost:3000/";

let completedRequests = 0;
let startTime;

async function sendRequest() {
  return new Promise((resolve, reject) => {
    http.get(TARGET_URL, (res) => {
      res.on("data", () => {});
      res.on("end", () => {
        completedRequests++;
        resolve();
      });
    }).on("error", (err) => {
      reject(err);
    });
  });
}

async function runLoadTest() {
  startTime = Date.now();
  const workers = Array.from({ length: CONCURRENCY }, async () => {
    while (completedRequests < TOTAL_REQUESTS) {
      await sendRequest();
    }
  });

  await Promise.all(workers);
  const endTime = Date.now();
  const duration = (endTime - startTime) / 1000;
  const rps = TOTAL_REQUESTS / duration;
  console.log(`Requests per second: ${rps.toFixed(2)}`);
}

runLoadTest().catch(console.error);

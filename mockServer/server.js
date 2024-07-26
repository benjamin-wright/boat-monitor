const express = require('express');
const app = express();
const fs = require('fs');

app.get('/', (req, res) => {
  const data = fs.readFileSync('../data/index.html');
  res.send(data.toString());
});

app.get('/index.html', (req, res) => {
  const data = fs.readFileSync('../data/index.html');
  res.send(data.toString());
});

app.get('/pins', (req, res) => {
  res.json({
    battery: Math.random() * 5.5 + 10,
    bilge: Math.random(),
  });
});

app.listen(3000, () => {
  console.log('Server is running on port 3000');
});
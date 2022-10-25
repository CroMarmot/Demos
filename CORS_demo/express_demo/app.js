const express = require('express')
const cors = require('cors')
const app = express()
const port = 5000

// app.use(cors()) <----------------------------

app.get('/', (req, res) => {
  console.log("execute");
  res.send('Hello World!')
})

app.post('/xxx', (req, res) => {
  console.log("execute");
  res.send('yyyyyyyy')
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})

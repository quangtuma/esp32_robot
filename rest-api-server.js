// import libraries
const express = require('express');
const { MongoClient } = require('mongodb');

// Init express app with port 3000
const app = express();
const port = 3000;
app.use(express.json());

// Connection URL
const url = 'mongodb://0.0.0.0:27017';
const mongoClient = new MongoClient(url);

// Database Name
const dbName = 'esp32';

async function main() {
  // Use connect method to connect to the server
  await mongoClient.connect();
  console.log('Connected successfully to MongoDB Server\n');
  const db = mongoClient.db(dbName);

  // CONTROLLING
  const controllingCollection = db.collection('controlling');
  const controllinResult = await controllingCollection.find({}).toArray();
  console.log('Found controlling =>', controllinResult, '\n');

  // GET endpoint to retrieve all controlling
  app.get('/api/controlling', async (req, res) => {
    const controlling = await controllingCollection.find({}).toArray();
    if (!controlling) console.log('Client request is not successfully!');
    res.json(controlling);
  });

  // GET endpoint to retrieve a single servo by ID
  app.get('/api/controlling/:findOne', async (req, res) => {
    const query = { servo: req.query.servo };
    const servo = await controllingCollection.findOne(query);
    if (!servo) return res.status(404).json({ error: 'servo not found' });
    res.json(servo);
  });

  // POST endpoint to add a new servo
  app.post('/api/controlling', async (req, res) => {
    const newservo = req.body;
    const result = await controllingCollection.insertOne(newservo);
    const insertedservo = await controllingCollection.findOne({ _id: result.insertedId });
    res.status(201).json(insertedservo);
  });

  // MODE
  const modeCollection = db.collection('mode');
  const modeResult = await modeCollection.find({}).toArray();
  console.log('Found mode =>', modeResult);

  // GET endpoint to retrieve mode
  app.get('/api/mode', async (req, res) => {
    const mode = await modeCollection.find({}).toArray();
    if (!mode) console.log('Client request is not successfully!');
    res.json(mode);
  });

  // Start the server
  app.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
  });

  return '\n';
}

main()
  .then(console.log)
  .catch(console.error);
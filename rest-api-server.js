const express = require('express');

// import { MongomongoClient } from 'mongodb'
const { MongoClient } = require('mongodb');


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
  console.log('Connected successfully to server');
  const db = mongoClient.db(dbName);
  const controllingCollection = db.collection('controlling');

  const findResult = await controllingCollection.find({}).toArray();
  console.log('Found documents =>', findResult);

  // GET endpoint to retrieve all controlling
  app.get('/api/controlling', async (req, res) => {
    const controlling = await controllingCollection.find({}).toArray();
    res.json(controlling);
    //console.log(res);
  });

  // GET endpoint to retrieve a single book by ID
  app.get('/api/controlling/:findOne', async (req, res) => {
    const query = { servo: req.query.servo };
    const book = await controllingCollection.findOne(query);
    if (!book) return res.status(404).json({ error: 'Book not found' });
    res.json(book);
  });

  // POST endpoint to add a new book
  app.post('/api/controlling', async (req, res) => {
    const newBook = req.body;
    const result = await controllingCollection.insertOne(newBook);
    const insertedBook = await controllingCollection.findOne({ _id: result.insertedId });
    res.status(201).json(insertedBook);
  });

  // Start the server
  app.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
  });

  return "done.";
}

main()
  .then(console.log)
  .catch(console.error);
const express = require('express');
const app = express();
const port = 3000;
app.use(express.json());

const { MongoClient } = require('mongodb');
// or as an es module:
// import { MongomongoClient } from 'mongodb'

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
    console.log(res);
  });

  // GET endpoint to retrieve a single book by ID
  app.get('/api/controlling/:id', async (req, res) => {
    var para = req.params.id;
    // const book = await controllingCollection.findOne({ servo: req.params, });
    // if (!book) return res.status(404).json({ error: 'Book not found' });
    // res.json(book);
    console.log(para);
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
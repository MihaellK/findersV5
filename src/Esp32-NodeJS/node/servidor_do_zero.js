const express = require("express");
const bodyParser = require("body-parser");
const urlencodedParser = bodyParser.urlencoded({ extended: false });

const sqlite3 = require("sqlite3").verbose();
const DBPATH = "dbUser.db";

const hostname = "127.0.0.1";
const port = 3081;
const app = express();

/* Servidor aplicação */

app.use(express.static("./"));

/* Definição dos endpoints */

/******** CRUD ************/

app.use(express.json());

app.get("/led1", (req, res) => {
  res.statusCode = 200;
  res.setHeader("Access-Control-Allow-Origin", "*"); // Isso é importante para evitar o erro de CORS

  // res.json({ ledStatus: 1 });
  var db = new sqlite3.Database(DBPATH); // Abre o banco
  var sql = "SELECT * FROM tbUser ORDER BY title COLLATE NOCASE";
  db.all(sql, [], (err, rows) => {
    if (err) {
      throw err;
    }
    res.json(rows);
  });
  db.close(); // Fecha o banco
});

app.post("/led1", function (req, res) {
  res.header("Access-Control-Allow-Origin", "*");
  console.log(req);
  console.log(req.body);
  console.log("Recebi um dado");
  // res.send("Inteli-COLLEGE f"uncionand!");
  res.json({ ledStatus: 1 });
});

app.post("/led0", function (req, res) {
  res.header("Access-Control-Allow-Origin", "*");
  console.log(req);
  console.log(req.body);
  console.log("Recebi um dado");
  // res.send("Inteli-COLLEGE f"uncionand!");
  res.json({ ledStatus: 0 });
});

app.listen(port, hostname, () => {
  console.log(`Page server running at http://${hostname}:${port}/`);
});

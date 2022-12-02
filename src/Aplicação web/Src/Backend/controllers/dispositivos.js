const service = require("../services/dispositivos");
require("express-async-errors");

const novosDispositivos = (req, res) => {
  const { nome, predio, sala, codigo_patrimonio, data_hora } = req.body;
  const dispositivo = new service.Dispositivo(
    nome,
    predio,
    sala,
    codigo_patrimonio,
    data_hora
  );

  dispositivo.createDispositivo().then((resul) => {
    if (resul.type === "error") {
      res.status(500).json({
        error: resul.message,
      });
    } else {
      res.status(200).json({
        message: resul.message,
      });
    }
  });

  return dispositivo;
};

const dispositivos = (req, res) => {
  const dispositivo = new service.Dispositivo();
  dispositivo.listarTodos().then((resul) => {
    if (resul.type === "error") {
      res.status(500).json({
        error: resul.message,
      });
    } else {
      res.status(200).json({
        message: resul.message,
      });
    }
  });
};

const dispositivoUnico = (req, res) => {
  const { codigo_patrimonio } = req.headers;
  const dispositivo = new service.Dispositivo();
  dispositivo.listarUnico(codigo_patrimonio).then((resul) => {
    if (resul.type === "error") {
      res.status(500).json({
        error: resul.message,
      });
    } else {
      res.status(200).json({
        message: resul.message,
      });
    }
  });
};

const editarDispositivo = (req, res) => {
  const { nome, predio, sala, data_hora, codigo_patrimonio } = req.body;
  const dispositivo = new service.Dispositivo();
  dispositivo
    .editarDispositivo(nome, predio, sala, data_hora, codigo_patrimonio)
    .then((resul) => {
      if (resul.type === "error") {
        res.status(500).json({
          error: resul.message,
        });
      } else {
        res.status(200).json({
          message: resul.message,
        });
      }
    });
};

const deletarDispositivo = (req, res) => {
  const { codigo_patrimonio } = req.body;
  const dispositivo = new service.Dispositivo();
  dispositivo.removeDispositivo(codigo_patrimonio).then((resul) => {
    if (resul.type === "error") {
      res.status(500).json({
        error: resul.message,
      });
    } else {
      res.status(200).json({
        message: resul.message,
      });
    }
  });
};

// essa parte está tornando a função pública
module.exports = {
  novosDispositivos,
  dispositivos,
  dispositivoUnico,
  editarDispositivo,
  deletarDispositivo,
};

const sqlite3 = require("sqlite3").verbose();
const sqlite = require("sqlite");
const { open } = require("sqlite");
class Dispositivo {
  constructor(nome, predio, sala, codigo_patrimonio, data_hora) {
    this.nome = nome;
    this.predio = predio;
    this.sala = sala;
    this.codigo_patrimonio = codigo_patrimonio;
    this.data_hora = data_hora;
  }

  async createDispositivo() {
    // Pegando a instancia do db
    const db = await sqlite.open({
      filename: "./database/dispositivos.db",
      driver: sqlite3.Database,
    });
    this.data_hora = "2022-11-23 18:58:27";
    // Inserindo as informações no db
    console.log(this.codigo_patrimonio);
    const inserction = await db.run(
      "INSERT INTO equipamentos (nome, predio, sala, data_hora, codigo_patrimonio) VALUES (?,?,?,CURRENT_TIMESTAMP, ?)",
      [this.nome, this.predio, this.sala, this.codigo_patrimonio]
    );
    await db.close();

    // Checando se todas as informações foram inseridas no db
    if (inserction.changes === 0) {
      const error = {
        type: "error",
        message: "Database error",
      };
      return error;
    }

    const sucess = {
      type: "sucess",
      message: "User created with sucess",
    };

    return sucess;
  }

  async listarTodos() {
    // Pegando a instancia do db
    const db = await sqlite.open({
      filename: "./database/dispositivos.db",
      driver: sqlite3.Database,
    });
    // Inserindo as informações no db
    const listagem = await db.all("SELECT * FROM equipamentos");
    console.log(listagem);
    await db.close();

    // Checando se todas as informações foram inseridas no db
    if (!listagem[0]) {
      const error = {
        type: "error",
        message: "Database error",
      };
      return error;
    }

    const sucess = {
      type: "sucess",
      message: listagem,
    };

    return sucess;
  }

  async listarUnico(codigo_patrimonio) {
    // Pegando a instancia do db
    const db = await sqlite.open({
      filename: "./database/dispositivos.db",
      driver: sqlite3.Database,
    });

    // Inserindo as informações no db
    const dispositivoUnico = await db.get(
      `SELECT *\ FROM equipamentos \ WHERE codigo_patrimonio = ${codigo_patrimonio}`
    );
    await db.close();

    // Checando se todas as informações foram inseridas no db
    if (!dispositivoUnico) {
      const error = {
        type: "error",
        message: "Database error",
      };
      return error;
    }

    const sucess = {
      type: "sucess",
      message: dispositivoUnico,
    };

    return sucess;
  }

  async editarDispositivo(nome, predio, sala, data_hora, codigo_patrimonio) {
    // Pegando a instancia do db
    const db = await sqlite.open({
      filename: "./database/dispositivos.db",
      driver: sqlite3.Database,
    });

    // seleção de um dispositivo a partir do código do patrimônio
    const dispositivoEdicao = await db.get(
      `SELECT * \ FROM equipamentos \ WHERE codigo_patrimonio = ${codigo_patrimonio}`
    );

    if (!dispositivoEdicao) {
      const error = {
        type: "error",
        message: "This device do not exist!",
      };
    }

    let queryComponents = [];

    if (nome) {
      queryComponents.push(`nome="${nome}"`);
    }

    if (predio) {
      queryComponents.push(`predio="${predio}"`);
    }

    if (sala) {
      queryComponents.push(`sala="${sala}"`);
    }

    console.log("queryComponents: ", queryComponents);

    const dispositivosConcatenados = queryComponents.join(",");

    console.log("dispositivosConcatenados: ", dispositivosConcatenados);

    const iniciacao = await db.run(
      `UPDATE equipamentos SET ${dispositivosConcatenados} WHERE codigo_patrimonio = ${codigo_patrimonio}`
    );

    if (iniciacao.changes === 0) {
      const error = {
        type: "error",
        message: "there was no change",
      };
    } else {
      const success = {
        type: "success",
        message: "update performed successfully",
      };
      return success;
    }
  }

  async removeDispositivo(codigo_patrimonio) {
    const db = await sqlite.open({
      filename: "./database/dispositivos.db",
      driver: sqlite3.Database,
    });

    if (!codigo_patrimonio) {
      const error = {
        type: "error",
        message: "This code do not exist!",
      };
      return error;
    }

    const dispositivoDeletado = await db.run(
      `DELETE \ FROM equipamentos \ WHERE codigo_patrimonio=${codigo_patrimonio}`
    );

    if (dispositivoDeletado.changes === 0) {
      const error = {
        type: "error",
        message: "Database error!",
      };
      return error;
    }

    const success = {
      type: "success",
      message: "Device deleted!",
    };
    return success;
  }
}

module.exports = { Dispositivo };

function popup() {
  document.getElementById("popup").style.display = "flex";
}
function closePopup() {
  document.getElementById("popup").style.display = "none";
}
const params = new URLSearchParams(window.location.search);
codigo_patrimonio = params.get("id");
debugger;
loadDevice(codigo_patrimonio);

async function loadDevice(codigo_patrimonio) {
  debugger;
  await $.ajax({
    url: "http://localhost:3001/dispositivos/unique",
    headers: { codigo_patrimonio: codigo_patrimonio },
    success: function (resul) {
      device = resul.message;
    },
  }).fail(function (err) {
    console.log(err.responseJSON.message);
  });
  console.log(device);
  listDevice(device);
}

async function listDevice(device) {
  var data = device.data_hora.slice(0, 10);
  var hora = device.data_hora.slice(11, 20);
  document.getElementById("infos").innerHTML = `
  <h2 class="card-title">Dados do dispositivo:</h2>
  <p class="card-title">Nome: <span>${device.nome}</span></p>
  <p class="card-title">Código de patrimônio: <span>${device.codigo_patrimonio}</span></p>

  <h3 class="card-title">Localização atual:</h3>
  <p class="card-title">Prédio: <span>${device.predio}</span></p>
  <p class="card-title">Sala: <span>${device.sala}</span></p>

  <h3 class="card-title">Última atualização: </h3>

  <p class="card-title">Data: <span>${data}</span></p>
  <p class="card-title">Hora: <span>${hora}</span></p>
        `;
}

function backPage() {
  window.location.href = `/HTML/EquipamGeral.html`;
}
function deletarDispositivo() {
    deleteDevice();
}

async function deleteDevice() {
    await $.ajax({
      url: "http://localhost:3001/dispositivos/delete",
      type: "DELETE",
      data: { codigo_patrimonio: device.codigo_patrimonio },
      success: async function (resul) {
        window.location.href = '/HTML/EquipamGeral.html'
      }
    }).fail(function (err) {
      console.log(err.responseJSON.message)
    })
  }
carregarDispositivos();

async function carregarDispositivos() {
  await $.ajax({
    url: "http://localhost:3001/dispositivos/",
    success: function (resul) {
      devices = resul.message
    }
  }).fail(function (err) {
    console.log(err.responseJSON.message)
  })
  console.log(devices)
  listDevices(devices);
}

async function listDevices(devices) {
  for (i = 0; i != devices.lenght; i++) {
    var inicial = devices[i].nome.slice(0,2);
    devices[i].nome = devices[i].nome.toUpperCase();
    inicial= inicial.toUpperCase();
    console.log(inicial);
    document.getElementById('listagem').innerHTML += `
    <button class="button" onclick="verDispositivo(${devices[i].codigo_patrimonio})">
    <div class="container">
    <div class="infos">
    <h1>${devices[i].nome} - ${devices[i].codigo_patrimonio}</h1>
    <p>Prédio: ${devices[i].predio}  - Sala: ${devices[i].sala}</p>
    </div>
    <div class="caixinha1">${inicial}</div>
    </div>
</button>  

<br>
`
  }

}

function verDispositivo(codigo_patrimonio){
    window.location.href = `/HTML/ResumoEquipam.html?id=${codigo_patrimonio}`;
    
}
var element = document.querySelector(".door");
element.addEventListener("click", toggleDoor);
function toggleDoor() {
    element.classList.toggle("doorOpen");

    database.ref('openDoor').set(element.classList.contains('doorOpen'));
}


const firebaseConfig = {
    apiKey: "AIzaSyBt3Vyfp1ze7VgCX5WGW9JAzyLrxPIGKkE",
    authDomain: "doorlock-ae216.firebaseapp.com",
    databaseURL: "https://doorlock-ae216-default-rtdb.europe-west1.firebasedatabase.app",
    projectId: "doorlock-ae216",
    storageBucket: "doorlock-ae216.appspot.com",
    messagingSenderId: "956949924574",
    appId: "1:956949924574:web:6f07256a9bced013d6504f",
    measurementId: "G-C0Z9Z7NV95"
};

const app = firebase.initializeApp(firebaseConfig);
const database = firebase.database();
const doorbell = database.ref("doorbell");


function showPopup() {
    document.getElementById('popup').style.display = 'flex';
}

function hidePopup() {
    document.getElementById('popup').style.display = 'none';
}


let doorbellValue = false;
doorbell.on("value", (snapshot) => {
    doorbellValue = snapshot.val();
    
})



document.getElementById('yesButton').addEventListener('click', function() {
    database.ref('doorbell').set(true);
    toggleDoor();
    hidePopup();

});

document.getElementById('noButton').addEventListener('click', function() {
    database.ref('doorbell').set(false);
    hidePopup();
});

database.ref('doorbell').on('value', function(snapshot) {
    if (snapshot.val() === true) {
        showPopup();
    }
});


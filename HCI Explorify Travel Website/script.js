let reservations = []; 

// Function to display reservations
function viewReservations() {
    const output = document.getElementById('output');
    if (reservations.length === 0) {
        output.innerHTML = '<p>No reservations found. Make one today!</p>';
        return;
    }

    let tableHTML = `
        <h3>My Reservations</h3>
        <table border="1">
            <thead>
                <tr>
                    <th>S.No</th>
                    <th>Date</th>
                    <th>Time</th>
                    <th>Train No</th>
                    <th>Destination</th>
                </tr>
            </thead>
            <tbody>
    `;
    reservations.forEach((res, index) => {
        tableHTML += `
            <tr>
                <td>${index + 1}</td>
                <td>${res.date}</td>
                <td>${res.time}</td>
                <td>${res.trainNo}</td>
                <td>${res.destination}</td>
            </tr>
        `;
    });
    tableHTML += '</tbody></table>';
    output.innerHTML = tableHTML;
}

// Function to create a new reservation
function createReservation() {
    const output = document.getElementById('output');
    output.innerHTML = `
        <h3>Create Reservation</h3>
        <form id="reservationForm">
            <label>Date:</label>
            <input type="date" id="date" required><br>
            <label>Time:</label>
            <input type="time" id="time" required><br>
            <label>Train No:</label>
            <input type="text" id="trainNo" required><br>
            <label>Destination:</label>
            <input type="text" id="destination" required><br>
            <button type="button" onclick="saveReservation()">Submit</button>
            <button type="reset">Reset</button>
            <button type="button" onclick="goToMainMenu()">Go to Main Menu</button>
        </form>
    `;
}

// Function to save a new reservation
function saveReservation() {
    const date = document.getElementById('date').value;
    const time = document.getElementById('time').value;
    const trainNo = document.getElementById('trainNo').value;
    const destination = document.getElementById('destination').value;

    if (date && time && trainNo && destination) {
        reservations.push({ date, time, trainNo, destination });
        alert('Reservation saved successfully!');
        goToMainMenu();
    } else {
        alert('Please fill out all fields.');
    }
}

// Function to cancel a reservation
function cancelReservation() {
    const output = document.getElementById('output');
    if (reservations.length === 0) {
        output.innerHTML = '<p>No reservations available to cancel.</p>';
        return;
    }

    let cancelHTML = '<h3>Cancel Reservation</h3>';
    reservations.forEach((res, index) => {
        cancelHTML += `
            <p>
                ${index + 1}. ${res.date} - ${res.destination} (Train: ${res.trainNo}) 
                <button onclick="removeReservation(${index})">Cancel</button>
            </p>
        `;
    });
    output.innerHTML = cancelHTML;
}

// Function to remove a reservation
function removeReservation(index) {
    reservations.splice(index, 1); // Remove reservation from array
    alert('Reservation canceled successfully!');
    cancelReservation(); // Refresh the cancellation list
}

// Function to change a reservation
function changeReservation() {
    const output = document.getElementById('output');
    if (reservations.length === 0) {
        output.innerHTML = '<p>No reservations available to change.</p>';
        return;
    }

    let changeHTML = '<h3>Change Reservation</h3>';
    reservations.forEach((res, index) => {
        changeHTML += `
            <p>
                ${index + 1}. ${res.date} - ${res.destination} (Train: ${res.trainNo}) 
                <button onclick="editReservation(${index})">Change</button>
            </p>
        `;
    });
    output.innerHTML = changeHTML;
}

// Function to edit a reservation
function editReservation(index) {
    const res = reservations[index];
    const output = document.getElementById('output');
    output.innerHTML = `
        <h3>Edit Reservation</h3>
        <form id="editReservationForm">
            <label>Date:</label>
            <input type="date" id="date" value="${res.date}" required><br>
            <label>Time:</label>
            <input type="time" id="time" value="${res.time}" required><br>
            <label>Train No:</label>
            <input type="text" id="trainNo" value="${res.trainNo}" required><br>
            <label>Destination:</label>
            <input type="text" id="destination" value="${res.destination}" required><br>
            <button type="button" onclick="saveEditedReservation(${index})">Save Changes</button>
            <button type="button" onclick="goToMainMenu()">Cancel</button>
        </form>
    `;
}

// Function to save edited reservation
function saveEditedReservation(index) {
    const date = document.getElementById('date').value;
    const time = document.getElementById('time').value;
    const trainNo = document.getElementById('trainNo').value;
    const destination = document.getElementById('destination').value;

    if (date && time && trainNo && destination) {
        reservations[index] = { date, time, trainNo, destination };
        alert('Reservation updated successfully!');
        goToMainMenu();
    } else {
        alert('Please fill out all fields.');
    }
}

// Function to return to the main menu
function goToMainMenu() {
    const output = document.getElementById('output');
    output.innerHTML = '<p>Select an option from the menu.</p>';
}

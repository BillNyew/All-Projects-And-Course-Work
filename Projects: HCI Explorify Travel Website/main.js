// Array to store all booking details
const bookings = []; // This already supports multiple bookings

// Function to navigate to a specific page
function navigate(pageId) {
    const pages = document.querySelectorAll('.page');
    pages.forEach(page => page.style.display = 'none');

    const targetPage = document.getElementById(pageId);
    if (targetPage) {
        targetPage.style.display = 'block';
        document.querySelectorAll('.nav a').forEach(link => link.classList.remove('active'));
        const activeLink = document.querySelector(`.nav a[href="#${pageId}"]`);
        if (activeLink) {
            activeLink.classList.add('active');
        }
    } else {
        console.error(`Page with ID '${pageId}' not found.`);
    }
}

// Open the booking modal for a destination
function openBookingModal(destination) {
    const bookingModal = document.createElement('div');
    bookingModal.id = 'booking-modal';
    bookingModal.style.position = 'fixed';
    bookingModal.style.top = '50%';
    bookingModal.style.left = '50%';
    bookingModal.style.transform = 'translate(-50%, -50%)';
    bookingModal.style.width = '50%';
    bookingModal.style.padding = '20px';
    bookingModal.style.backgroundColor = 'white';
    bookingModal.style.border = '2px solid #333';
    bookingModal.style.borderRadius = '10px';
    bookingModal.style.zIndex = '1000';
    bookingModal.style.boxShadow = '0 4px 8px rgba(0, 0, 0, 0.2)';
    bookingModal.innerHTML = `
        <h2>Book Your Trip to ${destination}</h2>
        <label for="trip-date">Select a date:</label>
        <input type="date" id="trip-date">
        <div style="margin-top: 20px;">
            <button id="confirm-booking">Confirm</button>
            <button id="cancel-booking-modal">Cancel</button>
        </div>
    `;

    document.body.appendChild(bookingModal);

    document.getElementById('confirm-booking').addEventListener('click', () => {
        const tripDate = document.getElementById('trip-date').value;
        if (tripDate) {
            // Save the booking with destination and date
            bookings.push({ destination, tripDate });
            alert(`Your trip to ${destination} on ${tripDate} has been booked.`);
            document.body.removeChild(bookingModal);
        } else {
            alert('Please select a valid date.');
        }
    });

    document.getElementById('cancel-booking-modal').addEventListener('click', () => {
        document.body.removeChild(bookingModal);
    });
}

// Open the Resources modal to view or cancel bookings
function openResourcesModal() {
    const resourcesModal = document.createElement('div');
    resourcesModal.id = 'resources-modal';
    resourcesModal.style.position = 'fixed';
    resourcesModal.style.top = '50%';
    resourcesModal.style.left = '50%';
    resourcesModal.style.transform = 'translate(-50%, -50%)';
    resourcesModal.style.width = '60%';
    resourcesModal.style.padding = '20px';
    resourcesModal.style.backgroundColor = 'white';
    resourcesModal.style.border = '2px solid #333';
    resourcesModal.style.borderRadius = '10px';
    resourcesModal.style.zIndex = '1000';
    resourcesModal.style.boxShadow = '0 4px 8px rgba(0, 0, 0, 0.2)';

    if (bookings.length === 0) {
        resourcesModal.innerHTML = `
            <h2>Your Bookings</h2>
            <p>No bookings found.</p>
            <button id="close-resources-modal">Close</button>
        `;
    } else {
        const bookingList = bookings.map(
            (b, index) => `<li>${b.destination} on ${b.tripDate} <button data-index="${index}" class="cancel-booking-btn">Cancel</button></li>`
        ).join('');

        resourcesModal.innerHTML = `
            <h2>Your Bookings</h2>
            <ul>${bookingList}</ul>
            <button id="close-resources-modal">Close</button>
        `;
    }

    document.body.appendChild(resourcesModal);

    document.getElementById('close-resources-modal').addEventListener('click', () => {
        document.body.removeChild(resourcesModal);
    });

    document.querySelectorAll('.cancel-booking-btn').forEach(button => {
        button.addEventListener('click', (event) => {
            const index = event.target.dataset.index;
            bookings.splice(index, 1); // Remove specific booking
            document.body.removeChild(resourcesModal);
            openResourcesModal(); // Reopen the modal with updated bookings
        });
    });
}

// Set up functionality for the navigation and buttons
function setupNavigation() {
    // Navigation buttons for destinations
    const navLinks = {
        '#transportation': 'destinations',
        '#destination': 'destinations',
        '#events': 'destinations'
    };

    Object.keys(navLinks).forEach(selector => {
        const link = document.querySelector(`.nav a[href="${selector}"]`);
        if (link) {
            link.addEventListener('click', () => navigate(navLinks[selector]));
        }
    });

    // Explorify logo to homepage
    const logo = document.querySelector('.logo');
    if (logo) {
        logo.addEventListener('click', () => navigate('home'));
    }

    // Resources tab functionality
    const resourcesTab = document.querySelector('.nav a[href="#resources"]');
    if (resourcesTab) {
        resourcesTab.addEventListener('click', openResourcesModal);
    }

    // Help tab functionality
    const helpTab = document.querySelector('.nav a[href="#help"]');
    if (helpTab) {
        helpTab.addEventListener('click', openResourcesModal);
    }
}

// Set up Book Now buttons on all pages
function setupBookNowButtons() {
    const bookNowButtons = document.querySelectorAll('.deal button');
    bookNowButtons.forEach(button => {
        const destination = button.closest('.deal').querySelector('h3').innerText;
        button.addEventListener('click', () => openBookingModal(destination));
    });
}

window.onload = function () {
    navigate('home'); // Start on the homepage
    setupNavigation(); // Set up global navigation
    setupBookNowButtons(); // Set up Book Now buttons
};

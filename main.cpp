#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;

// ========== ENUMERATIONS ========== //
// [Kareem] Define department and room type enumerations
enum Department
{
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

// [Kareem] Define room type enumerations
enum RoomType
{
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

// ========== ADDITIONAL ENUMERATIONS (Kareem's Task Extension) ========== //
// [Kareem] Define priority levels for emergency cases
enum EmergencyPriority
{
    CRITICAL, // Life-threatening condition
    URGENT,   // Serious but not immediately life-threatening
    STABLE    // Needs attention but can wait
};

// [Kareem] Define appointment status
enum AppointmentStatus
{
    SCHEDULED,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

// ========== PATIENT CLASS ========== //
// [Malak Soliman] Patient class definition and implementation
class Patient
{
private:
    int id;
    string name;
    int age;
    string contact;
    stack<string> medicalHistory;
    queue<string> testQueue;
    bool isAdmitted;
    RoomType roomType;

public:
    Patient(int pid, string n, int a, string c);

    void admitPatient(RoomType type);
    void dischargePatient();
    void addMedicalRecord(string record);
    void requestTest(string testName);
    string performTest();
    void displayHistory();

    int getId() const;
    string getName() const;
    bool getAdmissionStatus() const;
    string getRoomType() const;
};

// [Malak Soliman] Patient constructor implementation
Patient::Patient(int pid, string n, int a, string c)
{
    id = pid;
    name = n;
    age = a;
    contact = c;
    isAdmitted = false;
}

// [Malak Soliman] Admit patient to hospital
void Patient::admitPatient(RoomType type)
{
    isAdmitted = true;
    roomType = type;
    addMedicalRecord("Patient admitted to " + getRoomType() + " room type.");
}

// [Malak Soliman] Discharge patient from hospital
void Patient::dischargePatient()
{
    isAdmitted = false;
    addMedicalRecord("Patient discharged.");
}

// [Malak Soliman] Add medical record to patient history
void Patient::addMedicalRecord(string record)
{
    medicalHistory.push(record);
}

// [Malak Soliman] Request a medical test
void Patient::requestTest(string testName)
{
    testQueue.push(testName);
    addMedicalRecord("Test requested: " + testName);
}

// [Malak Soliman] Perform the next test in queue
string Patient::performTest()
{
    if (testQueue.empty())
    {
        return "No tests pending";
    }
    string testName = testQueue.front();
    testQueue.pop();
    addMedicalRecord("Test performed: " + testName);
    return testName;
}

// [Malak Soliman] Display patient medical history
void Patient::displayHistory()
{
    cout << "Medical History for " << name << ":" << endl;
    stack<string> tempStack;

    // Reverse the stack to show recent first
    while (!medicalHistory.empty())
    {
        tempStack.push(medicalHistory.top());
        medicalHistory.pop();
    }

    while (!tempStack.empty())
    {
        cout << "- " << tempStack.top() << endl;
        medicalHistory.push(tempStack.top());
        tempStack.pop();
    }
}

// [Malak Soliman] Get patient ID
int Patient::getId() const
{
    return id;
}

// [Malak Soliman] Get patient name
string Patient::getName() const
{
    return name;
}

// [Malak Soliman] Get admission status
bool Patient::getAdmissionStatus() const
{
    return isAdmitted;
}

// [Malak Soliman] Get room type as string
string Patient::getRoomType() const
{
    switch (roomType)
    {
    case GENERAL_WARD:
        return "General Ward";
    case ICU:
        return "ICU";
    case PRIVATE_ROOM:
        return "Private Room";
    case SEMI_PRIVATE:
        return "Semi-Private";
    default:
        return "Unknown";
    }
}

// ========== DOCTOR CLASS ========== //
// [Hanna] Doctor class definition and implementation
class Doctor
{
private:
    int id;
    string name;
    Department department;
    queue<int> appointmentQueue;

public:
    Doctor(int did, string n, Department d);

    void addAppointment(int patientId);
    int seePatient();

    int getId() const;
    string getName() const;
    string getDepartment() const;
};

// [Hanna] Doctor constructor implementation
Doctor::Doctor(int did, string n, Department d)
{
    id = did;
    name = n;
    department = d;
}

// [Hanna] Add appointment to doctor's queue
void Doctor::addAppointment(int patientId)
{
    appointmentQueue.push(patientId);
}

// [Hanna] See next patient in queue
int Doctor::seePatient()
{
    if (appointmentQueue.empty())
    {
        return -1;
    }
    int patientId = appointmentQueue.front();
    appointmentQueue.pop();
    return patientId;
}

// [Hanna] Get doctor ID
int Doctor::getId() const
{
    return id;
}

// [Hanna] Get doctor name
string Doctor::getName() const
{
    return name;
}

// [Hanna] Get department name as string
string Doctor::getDepartment() const
{
    switch (department)
    {
    case CARDIOLOGY:
        return "Cardiology";
    case NEUROLOGY:
        return "Neurology";
    case ORTHOPEDICS:
        return "Orthopedics";
    case PEDIATRICS:
        return "Pediatrics";
    case EMERGENCY:
        return "Emergency";
    case GENERAL:
        return "General";
    default:
        return "Unknown";
    }
}

// ========== APPOINTMENT CLASS (Kareem's Task) ========== //
// [Kareem] Appointment class to track detailed appointment information
class Appointment
{
private:
    int appointmentId;
    int doctorId;
    int patientId;
    string dateTime;
    AppointmentStatus status;

public:
    Appointment(int aid, int did, int pid, string dt);

    void setStatus(AppointmentStatus newStatus);
    int getAppointmentId() const;
    int getDoctorId() const;
    int getPatientId() const;
    string getDateTime() const;
    string getStatus() const;
};

// [Kareem] Appointment constructor implementation
Appointment::Appointment(int aid, int did, int pid, string dt)
{
    appointmentId = aid;
    doctorId = did;
    patientId = pid;
    dateTime = dt;
    status = SCHEDULED;
}

// [Kareem] Set appointment status
void Appointment::setStatus(AppointmentStatus newStatus)
{
    status = newStatus;
}

// [Kareem] Get appointment ID
int Appointment::getAppointmentId() const
{
    return appointmentId;
}

// [Kareem] Get doctor ID
int Appointment::getDoctorId() const
{
    return doctorId;
}

// [Kareem] Get patient ID
int Appointment::getPatientId() const
{
    return patientId;
}

// [Kareem] Get date and time
string Appointment::getDateTime() const
{
    return dateTime;
}

// [Kareem] Get status as string
string Appointment::getStatus() const
{
    switch (status)
    {
    case SCHEDULED:
        return "Scheduled";
    case IN_PROGRESS:
        return "In Progress";
    case COMPLETED:
        return "Completed";
    case CANCELLED:
        return "Cancelled";
    default:
        return "Unknown";
    }
}

// ========== HOSPITAL CLASS ========== //
// [Mazen Mohamed] Hospital class definition and implementation
class Hospital
{
protected:
    vector<Patient> patients;
    vector<Doctor> doctors;
    queue<int> emergencyQueue;
    int patientCounter;
    int doctorCounter;

public:
    Hospital();

    int registerPatient(string name, int age, string contact);
    int addDoctor(string name, Department dept);
    void admitPatient(int patientId, RoomType type);
    void addEmergency(int patientId);
    int handleEmergency();
    void bookAppointment(int doctorId, int patientId);
    void displayPatientInfo(int patientId);
    void displayDoctorInfo(int doctorId);
    void displayAllPatients();
    void displayAllDoctors();
};

// [Mazen Mohamed] Hospital constructor implementation
Hospital::Hospital()
{
    patientCounter = 1;
    doctorCounter = 1;
}

// [Mazen Mohamed] Register a new patient
int Hospital::registerPatient(string name, int age, string contact)
{
    Patient newPatient(patientCounter, name, age, contact);
    patients.push_back(newPatient);
    return patientCounter++;
}

// [Mazen Mohamed] Add a new doctor
int Hospital::addDoctor(string name, Department dept)
{
    Doctor newDoctor(doctorCounter, name, dept);
    doctors.push_back(newDoctor);
    return doctorCounter++;
}

// [Mazen Mohamed] Admit a patient
void Hospital::admitPatient(int patientId, RoomType type)
{
    for (auto &patient : patients)
    {
        if (patient.getId() == patientId)
        {
            patient.admitPatient(type);
            return;
        }
    }
    cout << "Patient with ID " << patientId << " not found." << endl;
}

// [Mazen Mohamed] Add emergency case
void Hospital::addEmergency(int patientId)
{
    emergencyQueue.push(patientId);
}

// [Mazen Mohamed] Handle emergency case
int Hospital::handleEmergency()
{
    if (emergencyQueue.empty())
    {
        cout << "No emergencies in queue." << endl;
        return -1;
    }
    int nextEmergency = emergencyQueue.front();
    emergencyQueue.pop();
    return nextEmergency;
}

// [Mazen Mohamed] Book appointment
void Hospital::bookAppointment(int doctorId, int patientId)
{
    for (auto &doctor : doctors)
    {
        if (doctor.getId() == doctorId)
        {
            doctor.addAppointment(patientId);

            // Log appointment in patient's medical history
            for (auto &patient : patients)
            {
                if (patient.getId() == patientId)
                {
                    patient.addMedicalRecord("Appointment booked with Doctor ID: " + to_string(doctorId));
                    return;
                }
            }
            cout << "Patient with ID " << patientId << " not found." << endl;
            return;
        }
    }
    cout << "Doctor with ID " << doctorId << " not found." << endl;
}

// [Mazen Mohamed] Display patient information
void Hospital::displayPatientInfo(int patientId)
{
    for (auto &patient : patients)
    {
        if (patient.getId() == patientId)
        {
            cout << "Patient ID: " << patient.getId() << endl;
            cout << "Name: " << patient.getName() << endl;
            cout << "Age: " << patient.getId() << endl;
            cout << "Contact: " << patient.getName() << endl;
            cout << "Admission Status: " << (patient.getAdmissionStatus() ? "Admitted" : "Not Admitted") << endl;
            if (patient.getAdmissionStatus())
            {
                cout << "Room Type: " << patient.getRoomType() << endl;
            }
            patient.displayHistory();
            return;
        }
    }
    cout << "Patient with ID " << patientId << " not found." << endl;
}

// [Mazen Mohamed] Display doctor information
void Hospital::displayDoctorInfo(int doctorId)
{
    for (auto &doctor : doctors)
    {
        if (doctor.getId() == doctorId)
        {
            cout << "Doctor ID: " << doctor.getId() << endl;
            cout << "Name: " << doctor.getName() << endl;
            cout << "Department: " << doctor.getDepartment() << endl;
            return;
        }
    }
    cout << "Doctor with ID " << doctorId << " not found." << endl;
}

// [Mazen Mohamed] Display all patients
void Hospital::displayAllPatients()
{
    cout << "===== ALL PATIENTS =====" << endl;
    for (auto &patient : patients)
    {
        cout << "ID: " << patient.getId() << " | Name: " << patient.getName() << " | Status: " << (patient.getAdmissionStatus() ? "Admitted" : "Not Admitted") << endl;
    }
    cout << "========================" << endl;
}

// [Mazen Mohamed] Display all doctors
void Hospital::displayAllDoctors()
{
    cout << "===== ALL DOCTORS =====" << endl;
    for (auto &doctor : doctors)
    {
        cout << "ID: " << doctor.getId() << " | Name: " << doctor.getName() << " | Department: " << doctor.getDepartment() << endl;
    }
    cout << "=======================" << endl;
}

// ========== EXTENDED HOSPITAL CLASS (Mazen's Task Extension) ========== //
// [Mazen Mohamed] Extended Hospital class with additional functionality
class ExtendedHospital : public Hospital
{
private:
    vector<Appointment> appointments;
    int appointmentCounter;
    map<int, EmergencyPriority> emergencyPriorities;

public:
    ExtendedHospital();

    int scheduleAppointment(int doctorId, int patientId, string dateTime);
    void updateAppointmentStatus(int appointmentId, AppointmentStatus status);
    void displayAppointmentInfo(int appointmentId);
    void setEmergencyPriority(int patientId, EmergencyPriority priority);
    vector<int> getEmergencyQueueByPriority();
    void displayAllAppointments();
};

// [Mazen Mohamed] Extended Hospital constructor implementation
ExtendedHospital::ExtendedHospital() : Hospital()
{
    appointmentCounter = 1;
}

// [Mazen Mohamed] Schedule a new appointment with date/time
int ExtendedHospital::scheduleAppointment(int doctorId, int patientId, string dateTime)
{
    // Check if doctor exists
    bool doctorExists = false;
    for (const auto &doctor : doctors)
    {
        if (doctor.getId() == doctorId)
        {
            doctorExists = true;
            break;
        }
    }

    if (!doctorExists)
    {
        cout << "Doctor with ID " << doctorId << " not found." << endl;
        return -1;
    }

    // Check if patient exists
    bool patientExists = false;
    for (const auto &patient : patients)
    {
        if (patient.getId() == patientId)
        {
            patientExists = true;
            break;
        }
    }

    if (!patientExists)
    {
        cout << "Patient with ID " << patientId << " not found." << endl;
        return -1;
    }

    // Create and add appointment
    Appointment newAppointment(appointmentCounter, doctorId, patientId, dateTime);
    appointments.push_back(newAppointment);

    // Also book appointment in the base class system
    bookAppointment(doctorId, patientId);

    return appointmentCounter++;
}

// [Mazen Mohamed] Update appointment status
void ExtendedHospital::updateAppointmentStatus(int appointmentId, AppointmentStatus status)
{
    for (auto &appointment : appointments)
    {
        if (appointment.getAppointmentId() == appointmentId)
        {
            appointment.setStatus(status);
            return;
        }
    }
    cout << "Appointment with ID " << appointmentId << " not found." << endl;
}

// [Mazen Mohamed] Display appointment information
void ExtendedHospital::displayAppointmentInfo(int appointmentId)
{
    for (const auto &appointment : appointments)
    {
        if (appointment.getAppointmentId() == appointmentId)
        {
            cout << "Appointment ID: " << appointment.getAppointmentId() << endl;
            cout << "Doctor ID: " << appointment.getDoctorId() << endl;
            cout << "Patient ID: " << appointment.getPatientId() << endl;
            cout << "Date/Time: " << appointment.getDateTime() << endl;
            cout << "Status: " << appointment.getStatus() << endl;
            return;
        }
    }
    cout << "Appointment with ID " << appointmentId << " not found." << endl;
}

// [Mazen Mohamed] Set emergency priority for a patient
void ExtendedHospital::setEmergencyPriority(int patientId, EmergencyPriority priority)
{
    emergencyPriorities[patientId] = priority;
}

// [Mazen Mohamed] Get emergency queue sorted by priority
vector<int> ExtendedHospital::getEmergencyQueueByPriority()
{
    // This would require a more complex implementation in a real system
    // For simplicity, we'll just return the regular emergency queue for now
    vector<int> result;

    // Create a copy of the emergency queue
    queue<int> tempQueue = emergencyQueue;

    while (!tempQueue.empty())
    {
        result.push_back(tempQueue.front());
        tempQueue.pop();
    }

    return result;
}

// [Mazen Mohamed] Display all appointments
void ExtendedHospital::displayAllAppointments()
{
    cout << "===== ALL APPOINTMENTS =====" << endl;
    for (const auto &appointment : appointments)
    {
        cout << "ID: " << appointment.getAppointmentId() << " | Doctor: " << appointment.getDoctorId()
            << " | Patient: " << appointment.getPatientId() << " | Time: " << appointment.getDateTime()
            << " | Status: " << appointment.getStatus() << endl;
    }
    cout << "============================" << endl;
}

// ========== INTERACTIVE MENU SYSTEM ========== //
// [Kareem & Mazen] Interactive menu system for hospital management
void displayMainMenu()
{
    cout << "\n=== HOSPITAL MANAGEMENT SYSTEM ===" << endl;
    cout << "1. Patient Management" << endl;
    cout << "2. Doctor Management" << endl;
    cout << "3. Appointment Management" << endl;
    cout << "4. Emergency Management" << endl;
    cout << "5. View Information" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

void displayPatientMenu()
{
    cout << "\n=== PATIENT MANAGEMENT ===" << endl;
    cout << "1. Register New Patient" << endl;
    cout << "2. Admit Patient" << endl;
    cout << "3. Discharge Patient" << endl;
    cout << "4. Request Test for Patient" << endl;
    cout << "5. Perform Test for Patient" << endl;
    cout << "6. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

void displayDoctorMenu()
{
    cout << "\n=== DOCTOR MANAGEMENT ===" << endl;
    cout << "1. Add New Doctor" << endl;
    cout << "2. View Doctor Details" << endl;
    cout << "3. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

void displayAppointmentMenu()
{
    cout << "\n=== APPOINTMENT MANAGEMENT ===" << endl;
    cout << "1. Book Appointment" << endl;
    cout << "2. Schedule Appointment (with date/time)" << endl;
    cout << "3. Update Appointment Status" << endl;
    cout << "4. View Appointment Details" << endl;
    cout << "5. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

void displayEmergencyMenu()
{
    cout << "\n=== EMERGENCY MANAGEMENT ===" << endl;
    cout << "1. Add Emergency Case" << endl;
    cout << "2. Handle Next Emergency" << endl;
    cout << "3. Set Emergency Priority" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

void displayViewMenu()
{
    cout << "\n=== VIEW INFORMATION ===" << endl;
    cout << "1. View All Patients" << endl;
    cout << "2. View Patient Details" << endl;
    cout << "3. View All Doctors" << endl;
    cout << "4. View Doctor Details" << endl;
    cout << "5. View All Appointments" << endl;
    cout << "6. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

// Helper function to get department from user
Department getDepartmentFromUser()
{
    int choice;
    cout << "Select Department:" << endl;
    cout << "1. Cardiology" << endl;
    cout << "2. Neurology" << endl;
    cout << "3. Orthopedics" << endl;
    cout << "4. Pediatrics" << endl;
    cout << "5. Emergency" << endl;
    cout << "6. General" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        return CARDIOLOGY;
    case 2:
        return NEUROLOGY;
    case 3:
        return ORTHOPEDICS;
    case 4:
        return PEDIATRICS;
    case 5:
        return EMERGENCY;
    case 6:
        return GENERAL;
    default:
        return GENERAL;
    }
}

// Helper function to get room type from user
RoomType getRoomTypeFromUser()
{
    int choice;
    cout << "Select Room Type:" << endl;
    cout << "1. General Ward" << endl;
    cout << "2. ICU" << endl;
    cout << "3. Private Room" << endl;
    cout << "4. Semi-Private" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        return GENERAL_WARD;
    case 2:
        return ICU;
    case 3:
        return PRIVATE_ROOM;
    case 4:
        return SEMI_PRIVATE;
    default:
        return GENERAL_WARD;
    }
}

// Helper function to get emergency priority from user
EmergencyPriority getEmergencyPriorityFromUser()
{
    int choice;
    cout << "Select Emergency Priority:" << endl;
    cout << "1. Critical" << endl;
    cout << "2. Urgent" << endl;
    cout << "3. Stable" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        return CRITICAL;
    case 2:
        return URGENT;
    case 3:
        return STABLE;
    default:
        return STABLE;
    }
}

// Helper function to get appointment status from user
AppointmentStatus getAppointmentStatusFromUser()
{
    int choice;
    cout << "Select Appointment Status:" << endl;
    cout << "1. Scheduled" << endl;
    cout << "2. In Progress" << endl;
    cout << "3. Completed" << endl;
    cout << "4. Cancelled" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        return SCHEDULED;
    case 2:
        return IN_PROGRESS;
    case 3:
        return COMPLETED;
    case 4:
        return CANCELLED;
    default:
        return SCHEDULED;
    }
}

// ========== MAIN PROGRAM ========== //
// [Kareem] Main function implementation with interactive menu
int main()
{
    ExtendedHospital hospital;
    int choice;

    // Sample data for testing
    hospital.registerPatient("John Doe", 35, "555-1234");
    hospital.registerPatient("Jane Smith", 28, "555-5678");
    hospital.addDoctor("Dr. Smith", CARDIOLOGY);
    hospital.addDoctor("Dr. Brown", NEUROLOGY);

    do
    {
        displayMainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        { // Patient Management
            int patientChoice;
            do
            {
                displayPatientMenu();
                cin >> patientChoice;

                switch (patientChoice)
                {
                case 1:
                { // Register New Patient
                    string name, contact;
                    int age;
                    cout << "Enter patient name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter patient age: ";
                    cin >> age;
                    cout << "Enter patient contact: ";
                    cin.ignore();
                    getline(cin, contact);

                    int id = hospital.registerPatient(name, age, contact);
                    cout << "Patient registered successfully with ID: " << id << endl;
                    break;
                }
                case 2:
                { // Admit Patient
                    int patientId;
                    cout << "Enter patient ID: ";
                    cin >> patientId;
                    RoomType roomType = getRoomTypeFromUser();
                    hospital.admitPatient(patientId, roomType);
                    cout << "Patient admitted successfully." << endl;
                    break;
                }
                case 3:
                { // Discharge Patient
                    // This would require adding a dischargePatient method to Hospital class
                    cout << "Discharge functionality would be implemented here." << endl;
                    break;
                }
                case 4:
                { // Request Test
                    // This would require access to the Patient object
                    cout << "Test request functionality would be implemented here." << endl;
                    break;
                }
                case 5:
                { // Perform Test
                    // This would require access to the Patient object
                    cout << "Test performance functionality would be implemented here." << endl;
                    break;
                }
                case 6: // Back to Main Menu
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (patientChoice != 6);
            break;
        }
        case 2:
        { // Doctor Management
            int doctorChoice;
            do
            {
                displayDoctorMenu();
                cin >> doctorChoice;

                switch (doctorChoice)
                {
                case 1:
                { // Add New Doctor
                    string name;
                    cout << "Enter doctor name: ";
                    cin.ignore();
                    getline(cin, name);
                    Department dept = getDepartmentFromUser();

                    int id = hospital.addDoctor(name, dept);
                    cout << "Doctor added successfully with ID: " << id << endl;
                    break;
                }
                case 2:
                { // View Doctor Details
                    int doctorId;
                    cout << "Enter doctor ID: ";
                    cin >> doctorId;
                    hospital.displayDoctorInfo(doctorId);
                    break;
                }
                case 3: // Back to Main Menu
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (doctorChoice != 3);
            break;
        }
        case 3:
        { // Appointment Management
            int appointmentChoice;
            do
            {
                displayAppointmentMenu();
                cin >> appointmentChoice;

                switch (appointmentChoice)
                {
                case 1:
                { // Book Appointment
                    int doctorId, patientId;
                    cout << "Enter doctor ID: ";
                    cin >> doctorId;
                    cout << "Enter patient ID: ";
                    cin >> patientId;
                    hospital.bookAppointment(doctorId, patientId);
                    cout << "Appointment booked successfully." << endl;
                    break;
                }
                case 2:
                { // Schedule Appointment with date/time
                    int doctorId, patientId;
                    string dateTime;
                    cout << "Enter doctor ID: ";
                    cin >> doctorId;
                    cout << "Enter patient ID: ";
                    cin >> patientId;
                    cout << "Enter date/time (e.g., 2023-10-15 10:00): ";
                    cin.ignore();
                    getline(cin, dateTime);

                    int aptId = hospital.scheduleAppointment(doctorId, patientId, dateTime);
                    if (aptId != -1)
                    {
                        cout << "Appointment scheduled successfully with ID: " << aptId << endl;
                    }
                    break;
                }
                case 3:
                { // Update Appointment Status
                    int appointmentId;
                    cout << "Enter appointment ID: ";
                    cin >> appointmentId;
                    AppointmentStatus status = getAppointmentStatusFromUser();
                    hospital.updateAppointmentStatus(appointmentId, status);
                    cout << "Appointment status updated successfully." << endl;
                    break;
                }
                case 4:
                { // View Appointment Details
                    int appointmentId;
                    cout << "Enter appointment ID: ";
                    cin >> appointmentId;
                    hospital.displayAppointmentInfo(appointmentId);
                    break;
                }
                case 5: // Back to Main Menu
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (appointmentChoice != 5);
            break;
        }
        case 4:
        { // Emergency Management
            int emergencyChoice;
            do
            {
                displayEmergencyMenu();
                cin >> emergencyChoice;

                switch (emergencyChoice)
                {
                case 1:
                { // Add Emergency Case
                    int patientId;
                    cout << "Enter patient ID: ";
                    cin >> patientId;
                    hospital.addEmergency(patientId);
                    cout << "Emergency case added successfully." << endl;
                    break;
                }
                case 2:
                { // Handle Next Emergency
                    int patientId = hospital.handleEmergency();
                    if (patientId != -1)
                    {
                        cout << "Handling emergency for patient ID: " << patientId << endl;
                    }
                    break;
                }
                case 3:
                { // Set Emergency Priority
                    int patientId;
                    cout << "Enter patient ID: ";
                    cin >> patientId;
                    EmergencyPriority priority = getEmergencyPriorityFromUser();
                    hospital.setEmergencyPriority(patientId, priority);
                    cout << "Emergency priority set successfully." << endl;
                    break;
                }
                case 4: // Back to Main Menu
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (emergencyChoice != 4);
            break;
        }
        case 5:
        { // View Information
            int viewChoice;
            do
            {
                displayViewMenu();
                cin >> viewChoice;

                switch (viewChoice)
                {
                case 1: // View All Patients
                    hospital.displayAllPatients();
                    break;
                case 2:
                { // View Patient Details
                    int patientId;
                    cout << "Enter patient ID: ";
                    cin >> patientId;
                    hospital.displayPatientInfo(patientId);
                    break;
                }
                case 3: // View All Doctors
                    hospital.displayAllDoctors();
                    break;
                case 4:
                { // View Doctor Details
                    int doctorId;
                    cout << "Enter doctor ID: ";
                    cin >> doctorId;
                    hospital.displayDoctorInfo(doctorId);
                    break;
                }
                case 5: // View All Appointments
                    hospital.displayAllAppointments();
                    break;
                case 6: // Back to Main Menu
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (viewChoice != 6);
            break;
        }
        case 6: // Exit
            cout << "Thank you for using Hospital Management System!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
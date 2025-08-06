#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define structures
typedef struct {
    int id;
    char name[50];
    int age;
    char position[20];
    char team[30];
} Player;

typedef struct {
    char name[50];
    char coach[50];
    int status; // 0=pending, 1=approved
} Team;

typedef struct {
    int matchId;
    char teamA[30];
    char teamB[30];
    char date[20];
    int scoreA;
    int scoreB;
} Match;

// Function prototypes
int login(char *username);
void registerUser();
void initializeFiles();
void adminMenu();
void coachMenu(char *username);
void playerMenu(char *username);
void approveTeams();
void scheduleMatch();
void enterResults();
void viewReports();
void createTeamRequest(char *username);
void addPlayers(char *username);
void viewMyTeam(char *username);
void viewMatches();
void viewProfile(char *username);
void viewTeamInfo(char *username);
void viewMatchSchedule();
void savePlayer(Player p);
void saveTeam(Team t);
void saveMatch(Match m);
void displayAllTeams();
void displayAllPlayers();
void displayAllMatches();

int main() {
    int choice, role;
    char username[50];

    printf("=== Soccer Management System ===\n");
    
    // Initialize all required files
    initializeFiles();

    while(1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                role = login(username);
                if(role == 0) continue; // login failed
                
                switch(role) {
                    case 1: adminMenu(); break;
                    case 2: coachMenu(username); break;
                    case 3: playerMenu(username); break;
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("Thank you for using Soccer Management System!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// Initialize all required files
void initializeFiles() {
    FILE *file;
    
    // Create users.txt with default admin account if it doesn't exist
    file = fopen("users.txt", "r");
    if(file == NULL) {
        file = fopen("users.txt", "w");
        if(file != NULL) {
            fprintf(file, "admin,admin123,admin\n");
            fclose(file);
            printf("Created users.txt with default admin account (username: admin, password: admin123)\n");
        } else {
            printf("Error creating users.txt file!\n");
        }
    } else {
        fclose(file);
    }
    
    // Create teams.txt if it doesn't exist
    file = fopen("teams.txt", "r");
    if(file == NULL) {
        file = fopen("teams.txt", "w");
        if(file != NULL) {
            fclose(file);
            printf("Created teams.txt file\n");
        } else {
            printf("Error creating teams.txt file!\n");
        }
    } else {
        fclose(file);
    }
    
    // Create team_requests.txt if it doesn't exist
    file = fopen("team_requests.txt", "r");
    if(file == NULL) {
        file = fopen("team_requests.txt", "w");
        if(file != NULL) {
            fclose(file);
            printf("Created team_requests.txt file\n");
        } else {
            printf("Error creating team_requests.txt file!\n");
        }
    } else {
        fclose(file);
    }
    
    // Create players.txt if it doesn't exist
    file = fopen("players.txt", "r");
    if(file == NULL) {
        file = fopen("players.txt", "w");
        if(file != NULL) {
            fclose(file);
            printf("Created players.txt file\n");
        } else {
            printf("Error creating players.txt file!\n");
        }
    } else {
        fclose(file);
    }
    
    // Create matches.txt if it doesn't exist
    file = fopen("matches.txt", "r");
    if(file == NULL) {
        file = fopen("matches.txt", "w");
        if(file != NULL) {
            fclose(file);
            printf("Created matches.txt file\n");
        } else {
            printf("Error creating matches.txt file!\n");
        }
    } else {
        fclose(file);
    }
    
    printf("File initialization complete!\n");
}

// Registration function
void registerUser() {
    char username[50], password[50], role[10];
    char confirmPassword[50];
    
    printf("\n=== User Registration ===\n");
    printf("Enter username: ");
    scanf("%s", username);
    
    // Check if username already exists
    FILE *file = fopen("users.txt", "r");
    if(file != NULL) {
        char fileUsername[50], filePassword[50], fileRole[10];
        while(fscanf(file, "%[^,],%[^,],%s\n", fileUsername, filePassword, fileRole) != EOF) {
            if(strcmp(username, fileUsername) == 0) {
                printf("Username already exists! Please choose a different username.\n");
                fclose(file);
                return;
            }
        }
        fclose(file);
    }
    
    printf("Enter password: ");
    scanf("%s", password);
    printf("Confirm password: ");
    scanf("%s", confirmPassword);
    
    if(strcmp(password, confirmPassword) != 0) {
        printf("Passwords do not match! Registration failed.\n");
        return;
    }
    
    printf("Select role:\n");
    printf("1. Coach\n");
    printf("2. Player\n");
    printf("Enter your choice: ");
    int roleChoice;
    scanf("%d", &roleChoice);
    
    switch(roleChoice) {
        case 1:
            strcpy(role, "coach");
            break;
        case 2:
            strcpy(role, "player");
            break;
        default:
            printf("Invalid role selection! Registration failed.\n");
            return;
    }
    
    // Save user to file
    file = fopen("users.txt", "a");
    if(file == NULL) {
        printf("Error creating user account!\n");
        return;
    }
    
    fprintf(file, "%s,%s,%s\n", username, password, role);
    fclose(file);
    
    printf("Registration successful! You can now login with your credentials.\n");
}

// Login function
int login(char *username) {
    char password[50];
    printf("\n=== Login ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *file = fopen("users.txt", "r");
    if(file == NULL) {
        printf("Error opening users file!\n");
        return 0;
    }

    char fileUsername[50], filePassword[50], role[10];
    while(fscanf(file, "%[^,],%[^,],%s\n", fileUsername, filePassword, role) != EOF) {
        if(strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            if(strcmp(role, "admin") == 0) return 1;
            else if(strcmp(role, "coach") == 0) return 2;
            else return 3; // player
        }
    }

    fclose(file);
    printf("Invalid username or password!\n");
    return 0;
}

// Admin menu
void adminMenu() {
    int choice;
    do {
        printf("\n=== Admin Menu ===\n");
        printf("1. Approve Teams\n");
        printf("2. Schedule Match\n");
        printf("3. Enter Match Results\n");
        printf("4. View Reports\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: approveTeams(); break;
            case 2: scheduleMatch(); break;
            case 3: enterResults(); break;
            case 4: viewReports(); break;
            case 5: printf("Logging out...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 5);
}

// Coach menu
void coachMenu(char *username) {
    int choice;
    do {
        printf("\n=== Coach Menu ===\n");
        printf("1. Create Team Request\n");
        printf("2. Add Players\n");
        printf("3. View My Team\n");
        printf("4. View Matches\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createTeamRequest(username); break;
            case 2: addPlayers(username); break;
            case 3: viewMyTeam(username); break;
            case 4: viewMatches(); break;
            case 5: printf("Logging out...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 5);
}

// Player menu
void playerMenu(char *username) {
    int choice;
    do {
        printf("\n=== Player Menu ===\n");
        printf("1. View Profile\n");
        printf("2. View Team Info\n");
        printf("3. View Match Schedule\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: viewProfile(username); break;
            case 2: viewTeamInfo(username); break;
            case 3: viewMatchSchedule(); break;
            case 4: printf("Logging out...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 4);
}

// Admin: Approve teams
void approveTeams() {
    printf("\n=== Pending Team Approvals ===\n");
    FILE *file = fopen("team_requests.txt", "r");
    if(file == NULL) {
        printf("No pending team requests!\n");
        return;
    }

    Team teams[20];
    int count = 0;
    while(fscanf(file, "%[^,],%[^,],%d\n", teams[count].name, teams[count].coach, &teams[count].status) != EOF) {
        if(teams[count].status == 0) { // pending
            printf("%d. Team: %s (Coach: %s)\n", count+1, teams[count].name, teams[count].coach);
            count++;
        }
    }
    fclose(file);

    if(count == 0) {
        printf("No pending team requests!\n");
        return;
    }

    int choice;
    printf("Enter team number to approve (0 to cancel): ");
    scanf("%d", &choice);

    if(choice > 0 && choice <= count) {
        teams[choice-1].status = 1; // approved
        FILE *out = fopen("teams.txt", "a");
        fprintf(out, "%s,%s,%d\n", teams[choice-1].name, teams[choice-1].coach, teams[choice-1].status);
        fclose(out);
        printf("Team %s approved!\n", teams[choice-1].name);
    }
}

// Admin: Schedule match
void scheduleMatch() {
    printf("\n=== Schedule New Match ===\n");
    displayAllTeams();

    Match m;
    printf("Enter match ID: ");
    scanf("%d", &m.matchId);
    printf("Enter team A: ");
    scanf("%s", m.teamA);
    printf("Enter team B: ");
    scanf("%s", m.teamB);
    printf("Enter date (DD-MM-YYYY): ");
    scanf("%s", m.date);
    m.scoreA = -1; // -1 means not played yet
    m.scoreB = -1;

    saveMatch(m);
    printf("Match scheduled successfully!\n");
}

// Admin: Enter match results
void enterResults() {
    printf("\n=== Enter Match Results ===\n");
    displayAllMatches();

    FILE *file = fopen("matches.txt", "r");
    if(file == NULL) {
        printf("No matches found!\n");
        return;
    }

    Match matches[20];
    int count = 0;
    while(fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%d\n",
          &matches[count].matchId, matches[count].teamA, matches[count].teamB,
          matches[count].date, &matches[count].scoreA, &matches[count].scoreB) != EOF) {
        if(matches[count].scoreA == -1) { // not played yet
            printf("%d. %s vs %s on %s\n", matches[count].matchId,
                   matches[count].teamA, matches[count].teamB, matches[count].date);
            count++;
        }
    }
    fclose(file);

    if(count == 0) {
        printf("No matches pending results!\n");
        return;
    }

    int matchId;
    printf("Enter match ID to update (0 to cancel): ");
    scanf("%d", &matchId);

    if(matchId == 0) return;

    int found = 0;
    for(int i = 0; i < count; i++) {
        if(matches[i].matchId == matchId) {
            printf("Enter score for %s: ", matches[i].teamA);
            scanf("%d", &matches[i].scoreA);
            printf("Enter score for %s: ", matches[i].teamB);
            scanf("%d", &matches[i].scoreB);
            found = 1;
            break;
        }
    }

    if(found) {
        // Rewrite the entire matches file with updated results
        FILE *out = fopen("matches.txt", "w");
        for(int i = 0; i < count; i++) {
            fprintf(out, "%d,%s,%s,%s,%d,%d\n",
                    matches[i].matchId, matches[i].teamA, matches[i].teamB,
                    matches[i].date, matches[i].scoreA, matches[i].scoreB);
        }
        fclose(out);
        printf("Match results updated!\n");
    } else {
        printf("Match ID not found!\n");
    }
}

// Admin: View reports
void viewReports() {
    int choice;
    do {
        printf("\n=== Reports Menu ===\n");
        printf("1. View All Teams\n");
        printf("2. View All Players\n");
        printf("3. View All Matches\n");
        printf("4. Back to Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayAllTeams(); break;
            case 2: displayAllPlayers(); break;
            case 3: displayAllMatches(); break;
            case 4: break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 4);
}

// Coach: Create team request
void createTeamRequest(char *username) {
    printf("\n=== Create Team Request ===\n");
    Team t;
    printf("Enter team name: ");
    scanf("%s", t.name);
    strcpy(t.coach, username);
    t.status = 0; // pending

    FILE *file = fopen("team_requests.txt", "a");
    if(file == NULL) {
        printf("Error creating team request!\n");
        return;
    }

    fprintf(file, "%s,%s,%d\n", t.name, t.coach, t.status);
    fclose(file);
    printf("Team request submitted for approval!\n");
}

// Coach: Add players
void addPlayers(char *username) {
    printf("\n=== Add Players ===\n");

    // First find the coach's team
    FILE *teamFile = fopen("teams.txt", "r");
    if(teamFile == NULL) {
        printf("No approved teams found!\n");
        return;
    }

    char teamName[50];
    int found = 0;
    Team t;
    while(fscanf(teamFile, "%[^,],%[^,],%d\n", t.name, t.coach, &t.status) != EOF) {
        if(strcmp(t.coach, username) == 0 && t.status == 1) {
            strcpy(teamName, t.name);
            found = 1;
            break;
        }
    }
    fclose(teamFile);

    if(!found) {
        printf("You don't have an approved team yet!\n");
        return;
    }

    Player p;
    printf("Enter player ID: ");
    scanf("%d", &p.id);
    printf("Enter player name: ");
    scanf("%s", p.name);
    printf("Enter age: ");
    scanf("%d", &p.age);
    printf("Enter position: ");
    scanf("%s", p.position);
    strcpy(p.team, teamName);

    savePlayer(p);
    printf("Player added to team %s!\n", teamName);
}

// Coach: View my team
void viewMyTeam(char *username) {
    printf("\n=== My Team ===\n");

    // Find the coach's team
    FILE *teamFile = fopen("teams.txt", "r");
    if(teamFile == NULL) {
        printf("No approved teams found!\n");
        return;
    }

    char teamName[50];
    int found = 0;
    Team t;
    while(fscanf(teamFile, "%[^,],%[^,],%d\n", t.name, t.coach, &t.status) != EOF) {
        if(strcmp(t.coach, username) == 0 && t.status == 1) {
            strcpy(teamName, t.name);
            found = 1;
            break;
        }
    }
    fclose(teamFile);

    if(!found) {
        printf("You don't have an approved team yet!\n");
        return;
    }

    printf("Team: %s\n", teamName);
    printf("Players:\n");

    FILE *playerFile = fopen("players.txt", "r");
    if(playerFile == NULL) {
        printf("No players found!\n");
        return;
    }

    Player p;
    int count = 0;
    while(fscanf(playerFile, "%d,%[^,],%d,%[^,],%s\n", &p.id, p.name, &p.age, p.position, p.team) != EOF) {
        if(strcmp(p.team, teamName) == 0) {
            printf("%d. %s (%s, age %d)\n", p.id, p.name, p.position, p.age);
            count++;
        }
    }
    fclose(playerFile);

    if(count == 0) {
        printf("No players in your team yet!\n");
    }
}

// Coach/Player: View matches
void viewMatches() {
    printf("\n=== All Matches ===\n");
    displayAllMatches();
}

// Player: View profile
void viewProfile(char *username) {
    printf("\n=== My Profile ===\n");

    FILE *file = fopen("players.txt", "r");
    if(file == NULL) {
        printf("Player data not found!\n");
        return;
    }

    Player p;
    int found = 0;
    while(fscanf(file, "%d,%[^,],%d,%[^,],%s\n", &p.id, p.name, &p.age, p.position, p.team) != EOF) {
        if(strcmp(p.name, username) == 0) {
            printf("ID: %d\n", p.id);
            printf("Name: %s\n", p.name);
            printf("Age: %d\n", p.age);
            printf("Position: %s\n", p.position);
            printf("Team: %s\n", p.team);
            found = 1;
            break;
        }
    }
    fclose(file);

    if(!found) {
        printf("Player not found!\n");
    }
}

// Player: View team info
void viewTeamInfo(char *username) {
    printf("\n=== My Team Info ===\n");

    // First find which team the player is on
    FILE *playerFile = fopen("players.txt", "r");
    if(playerFile == NULL) {
        printf("Player data not found!\n");
        return;
    }

    char teamName[50];
    int found = 0;
    Player p;
    while(fscanf(playerFile, "%d,%[^,],%d,%[^,],%s\n", &p.id, p.name, &p.age, p.position, p.team) != EOF) {
        if(strcmp(p.name, username) == 0) {
            strcpy(teamName, p.team);
            found = 1;
            break;
        }
    }
    fclose(playerFile);

    if(!found) {
        printf("Player not found on any team!\n");
        return;
    }

    // Now display team info
    FILE *teamFile = fopen("teams.txt", "r");
    if(teamFile == NULL) {
        printf("Team data not found!\n");
        return;
    }

    Team t;
    found = 0;
    while(fscanf(teamFile, "%[^,],%[^,],%d\n", t.name, t.coach, &t.status) != EOF) {
        if(strcmp(t.name, teamName) == 0) {
            printf("Team Name: %s\n", t.name);
            printf("Coach: %s\n", t.coach);
            found = 1;
            break;
        }
    }
    fclose(teamFile);

    if(!found) {
        printf("Team not found!\n");
        return;
    }

    // Display teammates
    printf("\nTeammates:\n");
    playerFile = fopen("players.txt", "r");
    if(playerFile == NULL) {
        printf("Error loading players!\n");
        return;
    }

    int count = 0;
    while(fscanf(playerFile, "%d,%[^,],%d,%[^,],%s\n", &p.id, p.name, &p.age, p.position, p.team) != EOF) {
        if(strcmp(p.team, teamName) == 0) {
            printf("%d. %s (%s)\n", p.id, p.name, p.position);
            count++;
        }
    }
    fclose(playerFile);

    printf("Total players: %d\n", count);
}

// Player: View match schedule
void viewMatchSchedule() {
    printf("\n=== Match Schedule ===\n");
    
    // First find which team the player is on
    char username[50];
    printf("Enter your name to find your team: ");
    scanf("%s", username);
    
    FILE *playerFile = fopen("players.txt", "r");
    if(playerFile == NULL) {
        printf("Player data not found!\n");
        return;
    }
    
    char teamName[50];
    int found = 0;
    Player p;
    
    while(fscanf(playerFile, "%d,%[^,],%d,%[^,],%s\n", 
          &p.id, p.name, &p.age, p.position, p.team) != EOF) {
        if(strcmp(p.name, username) == 0) {
            strcpy(teamName, p.team);
            found = 1;
            break;
        }
    }
    fclose(playerFile);
    
    if(!found) {
        printf("Player not found on any team!\n");
        return;
    }
    
    // Now find matches for this team
    FILE *matchFile = fopen("matches.txt", "r");
    if(matchFile == NULL) {
        printf("No matches scheduled yet!\n");
        return;
    }
    
    Match m;
    found = 0;
    printf("Upcoming matches for %s:\n", teamName);
    
    // Simplified match checking logic
    while(fscanf(matchFile, "%d,%[^,],%[^,],%[^,],%d,%d\n", 
          &m.matchId, m.teamA, m.teamB, m.date, &m.scoreA, &m.scoreB) != EOF) {
        
        int isTeamA = (strcmp(m.teamA, teamName) == 0);
        int isTeamB = (strcmp(m.teamB, teamName) == 0);
        int isUpcoming = (m.scoreA == -1);
        
        if((isTeamA || isTeamB) && isUpcoming) {
            printf("Match %d: %s vs %s on %s\n", 
                  m.matchId, m.teamA, m.teamB, m.date);
            found = 1;
        }
    }
    fclose(matchFile);
    
    if(!found) {
        printf("No upcoming matches for your team!\n");
    }
}

// Helper function to save a player
void savePlayer(Player p) {
    FILE *file = fopen("players.txt", "a");
    if(file == NULL) {
        printf("Error saving player!\n");
        return;
    }
    fprintf(file, "%d,%s,%d,%s,%s\n", p.id, p.name, p.age, p.position, p.team);
    fclose(file);
}

// Helper function to save a team
void saveTeam(Team t) {
    FILE *file = fopen("teams.txt", "a");
    if(file == NULL) {
        printf("Error saving team!\n");
        return;
    }
    fprintf(file, "%s,%s,%d\n", t.name, t.coach, t.status);
    fclose(file);
}

// Helper function to save a match
void saveMatch(Match m) {
    FILE *file = fopen("matches.txt", "a");
    if(file == NULL) {
        printf("Error saving match!\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%s,%d,%d\n", m.matchId, m.teamA, m.teamB, m.date, m.scoreA, m.scoreB);
    fclose(file);
}

// Helper function to display all teams
void displayAllTeams() {
    printf("\n=== All Teams ===\n");
    FILE *file = fopen("teams.txt", "r");
    if(file == NULL) {
        printf("No teams found!\n");
        return;
    }

    Team t;
    int count = 0;
    while(fscanf(file, "%[^,],%[^,],%d\n", t.name, t.coach, &t.status) != EOF) {
        if(t.status == 1) { // only show approved teams
            printf("%d. %s (Coach: %s)\n", ++count, t.name, t.coach);
        }
    }
    fclose(file);

    if(count == 0) {
        printf("No approved teams found!\n");
    }
}

// Helper function to display all players
void displayAllPlayers() {
    printf("\n=== All Players ===\n");
    FILE *file = fopen("players.txt", "r");
    if(file == NULL) {
        printf("No players found!\n");
        return;
    }

    Player p;
    int count = 0;
    while(fscanf(file, "%d,%[^,],%d,%[^,],%s\n", &p.id, p.name, &p.age, p.position, p.team) != EOF) {
        printf("%d. %s (%s, %s, age %d)\n", ++count, p.name, p.team, p.position, p.age);
    }
    fclose(file);

    if(count == 0) {
        printf("No players found!\n");
    }
}

// Helper function to display all matches
void displayAllMatches() {
    FILE *file = fopen("matches.txt", "r");
    if(file == NULL) {
        printf("No matches found!\n");
        return;
    }

    Match m;
    int count = 0;
    while(fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%d\n",
          &m.matchId, m.teamA, m.teamB, m.date, &m.scoreA, &m.scoreB) != EOF) {
        if(m.scoreA == -1) {
            printf("Upcoming: %s vs %s on %s\n", m.teamA, m.teamB, m.date);
        } else {
            printf("Completed: %s %d - %d %s on %s\n", m.teamA, m.scoreA, m.scoreB, m.teamB, m.date);
        }
        count++;
    }
    fclose(file);

    if(count == 0) {
        printf("No matches found!\n");
    }
}
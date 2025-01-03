#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
#include <algorithm> 
using namespace std;

class FlightRoutes {
    map<string, vector<pair<string, int>>> graph; 

    string toLower(const string& str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

public:

    void addRoute(const string& from, const string& to, int cost) {
        string lowerFrom = toLower(from);
        string lowerTo = toLower(to);
        graph[lowerFrom].push_back({lowerTo, cost});
        graph[lowerTo].push_back({lowerFrom, cost}); 
    }

   
    void findShortestPath(const string& start, const string& destination) {
        string lowerStart = toLower(start);
        string lowerDestination = toLower(destination);

        if (graph.find(lowerStart) == graph.end() || graph.find(lowerDestination) == graph.end()) {
            cout << "One or both cities do not exist in the graph.\n";
            return;
        }

        map<string, int> distances;
        for (auto& node : graph) distances[node.first] = INT_MAX;
        distances[lowerStart] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, lowerStart});

        while (!pq.empty()) {
            auto [dist, city] = pq.top();
            pq.pop();

            if (city == lowerDestination) {
                cout << "Shortest path cost from " << start << " to " << destination << ": Rs." << dist << endl;
                return;
            }

            for (auto& neighbor : graph[city]) {
                int newDist = dist + neighbor.second;
                if (newDist < distances[neighbor.first]) {
                    distances[neighbor.first] = newDist;
                    pq.push({newDist, neighbor.first});
                }
            }
        }

        cout << "No route found.\n";
    }


    void displayRoutes(const string& start, const string& destination) {
        string lowerStart = toLower(start);
        string lowerDestination = toLower(destination);

        if (graph.find(lowerStart) == graph.end() || graph.find(lowerDestination) == graph.end()) {
            cout << "One or both cities do not exist in the graph.\n";
            return;
        }

        map<string, bool> visited;
        vector<string> path;
        dfs(lowerStart, lowerDestination, visited, path);
    }

private:
    void dfs(const string& current, const string& destination, map<string, bool>& visited, vector<string>& path) {
        visited[current] = true;
        path.push_back(current);

        if (current == destination) {
            for (const auto& city : path) cout << city << " ";
            cout << endl;
        } else {
            for (const auto& neighbor : graph[current]) {
                if (!visited[neighbor.first]) dfs(neighbor.first, destination, visited, path);
            }
        }

        path.pop_back();
        visited[current] = false;
    }
};

int main() {
    FlightRoutes fr;

    vector<pair<pair<string, string>, int>> routes = {
        {{"Delhi", "Mumbai"}, 1200},
        {{"Delhi", "Bangalore"}, 2000},
        {{"Mumbai", "Chennai"}, 1500},
        {{"Bangalore", "Hyderabad"}, 800},
        {{"Kolkata", "Chennai"}, 1800},
        {{"Delhi", "Kolkata"}, 1500},
        {{"Kolkata", "Hyderabad"}, 1200},
        {{"Mumbai", "Ahmedabad"}, 600},
        {{"Ahmedabad", "Jaipur"}, 500},
        {{"Jaipur", "Delhi"}, 400},
        {{"Delhi", "Lucknow"}, 700},
        {{"Lucknow", "Varanasi"}, 300},
        {{"Varanasi", "Patna"}, 400},
        {{"Patna", "Ranchi"}, 350},
        {{"Ranchi", "Bhubaneswar"}, 500},
        {{"Bhubaneswar", "Kolkata"}, 400},
        {{"Chennai", "Coimbatore"}, 600},
        {{"Coimbatore", "Bangalore"}, 500},
        {{"Hyderabad", "Pune"}, 700},
        {{"Pune", "Mumbai"}, 300}
    };

  
    for (auto& route : routes) {
        fr.addRoute(route.first.first, route.first.second, route.second);
    }

    string start, destination;
    cout << "--- Flight Route System ---\n";
    cout << "List of cities: Delhi, Mumbai, Bangalore, Hyderabad, Chennai, Kolkata, Ahmedabad, Jaipur, Lucknow, Varanasi, Patna, Ranchi, Bhubaneswar, Pune, Coimbatore\n";

    cout << "Enter starting city: ";
    cin >> start;
    cout << "Enter destination city: ";
    cin >> destination;

    cout << "\n1. Find Shortest Path\n";
    cout << "2. Display All Routes\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Finding shortest path from " << start << " to " << destination << "...\n";
        fr.findShortestPath(start, destination);
    } else if (choice == 2) {
        cout << "Displaying all routes from " << start << " to " << destination << "...\n";
        fr.displayRoutes(start, destination);
    } else {
        cout << "Invalid choice. Exiting program.\n";
    }

    return 0;
}

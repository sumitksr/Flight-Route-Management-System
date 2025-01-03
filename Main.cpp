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
        map<string, string> previous;
        for (auto& node : graph) distances[node.first] = INT_MAX;
        distances[lowerStart] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, lowerStart});

        while (!pq.empty()) {
            auto [dist, city] = pq.top();
            pq.pop();

            if (city == lowerDestination) {
                vector<string> path;
                for (string at = lowerDestination; !at.empty(); at = previous[at]) {
                    path.push_back(at);
                }
                reverse(path.begin(), path.end());

                cout << "Shortest path cost from " << start << " to " << destination << ": Rs." << dist << endl;
                cout << "Path: ";
                for (const auto& p : path) cout << p << " ";
                cout << endl;
                return;
            }

            for (auto& neighbor : graph[city]) {
                int newDist = dist + neighbor.second;
                if (newDist < distances[neighbor.first]) {
                    distances[neighbor.first] = newDist;
                    previous[neighbor.first] = city;
                    pq.push({newDist, neighbor.first});
                }
            }
        }

        cout << "No route found.\n";
    }
};

int main() {
    FlightRoutes fr;

    vector<pair<pair<string, string>, int>> routes = {
        // Domestic routes
        {{"Delhi", "Mumbai"}, 1200},
        {{"Delhi", "Kolkata"}, 1500},
        {{"Mumbai", "Chennai"}, 1500},
        {{"Delhi", "Bangalore"}, 2000},
        {{"Kolkata", "Chennai"}, 1800},
        {{"Delhi", "Ahmedabad"}, 1000},
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
        {{"Pune", "Mumbai"}, 300},

        // Routes to International airports
        {{"Delhi", "Dubai"}, 5000},
        {{"Mumbai", "Dubai"}, 4500},
        {{"Kolkata", "Singapore"}, 5500},
        {{"Mumbai", "Singapore"}, 6000},
        {{"Delhi", "London"}, 20000},
        {{"Mumbai", "London"}, 21000},
        {{"Delhi", "New York"}, 35000},
        {{"Mumbai", "New York"}, 36000},
        {{"Kolkata", "Bangkok"}, 4500},
        {{"Delhi", "Bangkok"}, 4000},

        // International connections
        {{"Dubai", "London"}, 15000},
        {{"Dubai", "New York"}, 25000},
        {{"Singapore", "Bangkok"}, 3000},
        {{"London", "New York"}, 12000}
    };

    for (auto& route : routes) {
        fr.addRoute(route.first.first, route.first.second, route.second);
    }

    string start, destination;
    cout << "--- Flight Route System ---\n";
    cout << "List of cities: Delhi, Mumbai, Bangalore, Kolkata, Chennai, Ahmedabad, Jaipur, Lucknow, Varanasi, Patna, Ranchi, Bhubaneswar, Pune, Coimbatore, Hyderabad\n";
    cout << "International cities: Dubai, Singapore, London, New York, Bangkok\n";

    cout << "Enter starting city: ";
    cin >> start;
    cout << "Enter destination city: ";
    cin >> destination;

    cout << "\n1. Find Shortest Path\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Finding shortest path from " << start << " to " << destination << "...\n";
        fr.findShortestPath(start, destination);
    } else {
        cout << "Invalid choice. Exiting program.\n";
    }

    return 0;
}

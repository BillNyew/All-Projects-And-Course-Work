package HW6;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class ShortestPath {
    private Map<String, List<String>> graph;

    public ShortestPath() {
        graph = new HashMap<>();
        buildGraph();
    }

    private void buildGraph() {
        try (BufferedReader br = new BufferedReader(new FileReader("Dict.txt"))) {
            String word;
            while ((word = br.readLine()) != null) {
                addWordToGraph(word);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void addWordToGraph(String word) {
        graph.computeIfAbsent(word, k -> new ArrayList<>());
        for (String w : graph.keySet()) {
            if (isOneLetterDifferent(w, word)) {
                graph.get(w).add(word);
                graph.get(word).add(w);
            }
        }
    }

    private boolean isOneLetterDifferent(String word1, String word2) {
        if (word1.length() != word2.length()) {
            return false;
        }
        int diffCount = 0;
        for (int i = 0; i < word1.length(); i++) {
            if (word1.charAt(i) != word2.charAt(i)) {
                diffCount++;
            }
            if (diffCount > 1) {
                return false;
            }
        }
        return diffCount == 1;
    }

    public List<String> findShortestPath(String start, String end) {
        Queue<String> queue = new LinkedList<>();
        Map<String, String> parentMap = new HashMap<>();
        Set<String> visited = new HashSet<>();

        queue.add(start);
        visited.add(start);

        while (!queue.isEmpty()) {
            String current = queue.poll();

            if (current.equals(end)) {
                return reconstructPath(start, end, parentMap);
            }

            for (String neighbor : graph.get(current)) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.add(neighbor);
                    parentMap.put(neighbor, current);
                }
            }
        }

        return Collections.emptyList();
    }

    private List<String> reconstructPath(String start, String end, Map<String, String> parentMap) {
        List<String> path = new ArrayList<>();
        String current = end;
        while (!current.equals(start)) {
            path.add(0, current);
            current = parentMap.get(current);
        }
        path.add(0, start);
        return path;
    }
}
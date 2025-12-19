import java.io.*;
import java.net.*;
import java.util.*;

public class BCNode {
    private List<Block> blockchain;
    private int difficulty;
    private List<Socket> peerSockets;
    private List<ObjectOutputStream> outputStreams;
    private int port;

    public BCNode(int port, List<Integer> peerPorts) {
        this.blockchain = new ArrayList<>();
        this.difficulty = 4;
        this.peerSockets = new ArrayList<>();
        this.outputStreams = new ArrayList<>();
        this.port = port;

        // Start the server thread to accept incoming connections
        new Thread(new ConnectionHandler()).start();

        // Ensure the Genesis Block exists
        if (peerPorts.isEmpty()) {
            blockchain.add(new Block());
        } else {
            for (int peerPort : peerPorts) {
                connectToPeer("localhost", peerPort);
            }
        }

        if (blockchain.isEmpty()) {
            blockchain.add(new Block());
        }
    }

    private void connectToPeer(String address, int peerPort) {
        try {
            Socket socket = new Socket(address, peerPort);
            ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
            ObjectInputStream in = new ObjectInputStream(socket.getInputStream());
    
            peerSockets.add(socket);
            outputStreams.add(out);
    
            Thread.sleep(500); // Ensure proper connection setup
    
            new Thread(new ReadHandler(socket, in)).start();
            out.writeObject("REQUEST_CHAIN");
            out.flush();
            System.out.println("DEBUG: Connected to peer: " + address + ":" + peerPort);
        } catch (IOException | InterruptedException e) {
            System.err.println("DEBUG: Failed to connect to peer: " + address + ":" + peerPort);
        }
    }
    

    public void addBlock(Block newBlock) {
        newBlock.setPreviousHash(blockchain.get(blockchain.size() - 1).getHash());
        mineBlock(newBlock);

        if (validateBlock(newBlock)) {
            blockchain.add(newBlock);
            System.out.println("Block added successfully: " + newBlock.getHash());
            broadcastBlock(newBlock);
        } else {
            System.out.println("Block validation failed.");
        }
    }

    private void mineBlock(Block block) {
        String target = new String(new char[difficulty]).replace('\0', '0');
        long startTime = System.currentTimeMillis();

        while (!block.calculateBlockHash().substring(0, difficulty).equals(target)) {
            block.setNonce(block.getNonce() + 1);

            if (System.currentTimeMillis() - startTime > 60000) {
                System.out.println("Mining timeout. Block not mined.");
                return;
            }
        }
        block.setHash(block.calculateBlockHash());
        System.out.println("Block mined: " + block.getHash());
    }

    private boolean validateBlock(Block block) {
        String target = new String(new char[difficulty]).replace('\0', '0');
        return block.getHash().equals(block.calculateBlockHash()) &&
               block.getPreviousHash().equals(blockchain.get(blockchain.size() - 1).getHash()) &&
               block.getHash().substring(0, difficulty).equals(target);
    }

    private void broadcastBlock(Block block) {
        System.out.println("DEBUG: Broadcasting block " + block.getHash() + " to peers...");
        Iterator<ObjectOutputStream> it = outputStreams.iterator();
    
        while (it.hasNext()) {
            try {
                ObjectOutputStream out = it.next();
                out.writeObject(block);
                out.flush();
                System.out.println("DEBUG: Block sent successfully.");
            } catch (IOException e) {
                System.err.println("DEBUG: Failed to send block. Removing peer.");
                it.remove();
            }
        }
    }
    
  

    private class ConnectionHandler implements Runnable {
        @Override
        public void run() {
            try (ServerSocket serverSocket = new ServerSocket(port)) {
                System.out.println("BCNode listening on port " + port);
                while (true) {
                    Socket socket = serverSocket.accept();
                    ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
                    ObjectInputStream in = new ObjectInputStream(socket.getInputStream());

                    peerSockets.add(socket);
                    outputStreams.add(out);
                    new Thread(new ReadHandler(socket, in)).start();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private class ReadHandler implements Runnable {
        private Socket socket;
        private ObjectInputStream in;
    
        public ReadHandler(Socket socket, ObjectInputStream in) {
            this.socket = socket;
            this.in = in;
        }
    
        @Override
        public void run() {
            try {
                while (true) {
                    Object obj = in.readObject();
    
                    if (obj instanceof Block) {
                        Block receivedBlock = (Block) obj;
                        System.out.println("DEBUG: Received new block: " + receivedBlock.getHash());
    
                        if (validateBlock(receivedBlock)) {
                            blockchain.add(receivedBlock);
                            System.out.println("Block successfully added: " + receivedBlock.getHash());
                            broadcastBlock(receivedBlock);
                        } else {
                            System.out.println("Block validation failed: " + receivedBlock.getHash());
                        }
                    } else if (obj instanceof String && obj.equals("REQUEST_CHAIN")) {
                        System.out.println("DEBUG: Peer requested blockchain sync.");
                        ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
                        out.writeObject(blockchain);
                        out.flush();
                    }
                }
            } catch (IOException | ClassNotFoundException e) {
                System.out.println("Lost connection with peer. Removing from peer list.");
                peerSockets.remove(socket);
            }
        }
    }
    

    public static void main(String[] args) {
        Scanner keyScan = new Scanner(System.in);

        // Grab my port number on which to start this node
        System.out.print("Enter port to start (on current IP): ");
        while (!keyScan.hasNextInt()) {
            System.out.print("Invalid input. Enter a valid port number: ");
            keyScan.next();
        }
        int myPort = keyScan.nextInt();

        // Need to get what other Nodes to connect to
        System.out.print("Enter remote ports (current IP is assumed): ");
        keyScan.nextLine(); // Skip newline from previous input
        String line = keyScan.nextLine();
        List<Integer> remotePorts = new ArrayList<>();

        if (!line.trim().isEmpty()) { // Ensure input isn't empty
            String[] splitLine = line.split(" ");
            for (String s : splitLine) {
                try {
                    remotePorts.add(Integer.parseInt(s));
                } catch (NumberFormatException e) {
                    System.out.println("Invalid port number ignored: " + s);
                }
            }
        }

        // Create the Node
        BCNode n = new BCNode(myPort, remotePorts);

        String ip = "";
        try {
            ip = Inet4Address.getLocalHost().getHostAddress();
        } catch (UnknownHostException e) {
            e.printStackTrace();
            System.exit(1);
        }

        System.out.println("Node started on " + ip + ": " + myPort);

        // Node command line interface
        while (true) {
            System.out.println("\nNODE on port: " + myPort);
            System.out.println("1. Display Node's blockchain");
            System.out.println("2. Create/mine new Block");
            System.out.println("3. Kill Node");
            System.out.print("Enter option: ");

            if (!keyScan.hasNextInt()) {
                System.out.println("Invalid input. Please enter a number (1-3).");
                keyScan.next(); // Clear invalid input
                continue;
            }
            int in = keyScan.nextInt();

            if (in == 1) {
                System.out.println(n);
            } else if (in == 2) {
                // Grab the information to put in the block
                System.out.print("Enter information for new Block: ");
                keyScan.nextLine(); // Consume newline
                String blockInfo = keyScan.nextLine();
                Block b = new Block(blockInfo);
                n.addBlock(b);
            } else if (in == 3) {
                // Shutdown node
                keyScan.close();
                System.exit(0);
            } else {
                System.out.println("Invalid option. Please enter 1, 2, or 3.");
            }
        }
    }
}

package project2.singlenode;

import java.util.ArrayList;
import java.util.List;

public class BCNode1 {
    private List<Block1> blockchain;
    private int difficulty; // Number of leading zeros required for PoW

    // Constructor
    public BCNode1(int difficulty) {
        this.blockchain = new ArrayList<>();
        this.difficulty = difficulty;
        // Create and add the Genesis Block
        blockchain.add(new Block1());
    }

    // Method to add a block to the blockchain
    public void addBlock(Block1 newBlock) {
        // Set the previous hash of the new block to the last block's hash
        newBlock.setPreviousHash(blockchain.get(blockchain.size() - 1).getHash());
        
        // Mine the block to meet the PoW requirement
        mineBlock(newBlock);

        // Validate before adding
        if (validateBlock(newBlock)) {
            blockchain.add(newBlock);
            System.out.println("Block added successfully: " + newBlock.getHash());
        } else {
            System.out.println("Block validation failed. Not added to the chain.");
        }
    }

    // Proof of Work (Mining)
    private void mineBlock(Block1 block) {
        String target = new String(new char[difficulty]).replace('\0', '0'); // Required prefix of zeros
        while (!block.calculateBlockHash().substring(0, difficulty).equals(target)) {
            block.setNonce(block.getNonce() + 1);
        }
        // Update block's hash after successful mining
        block.setHash(block.calculateBlockHash());
        System.out.println("Block mined: " + block.getHash());
    }

    // Validate entire blockchain
    public boolean validateChain() {
        for (int i = 1; i < blockchain.size(); i++) {
            Block1 current = blockchain.get(i);
            Block1 previous = blockchain.get(i - 1);

            // Validate hash consistency
            if (!current.getHash().equals(current.calculateBlockHash())) {
                System.out.println("Block " + i + " has an invalid hash.");
                return false;
            }
            // Validate previousHash linkage
            if (!current.getPreviousHash().equals(previous.getHash())) {
                System.out.println("Block " + i + " has an invalid previous hash.");
                return false;
            }
            // Validate Proof of Work
            String target = new String(new char[difficulty]).replace('\0', '0');
            if (!current.getHash().substring(0, difficulty).equals(target)) {
                System.out.println("Block " + i + " does not meet Proof of Work criteria.");
                return false;
            }
        }
        return true;
    }

    // Validate a single block before adding it
    private boolean validateBlock(Block1 block) {
        String target = new String(new char[difficulty]).replace('\0', '0');

        return block.getHash().equals(block.calculateBlockHash()) &&
               block.getPreviousHash().equals(blockchain.get(blockchain.size() - 1).getHash()) &&
               block.getHash().substring(0, difficulty).equals(target);
    }

    // toString to display the blockchain
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Block1 block : blockchain) {
            sb.append(block.toString()).append("\n");
        }
        return sb.toString();
    }

    // Main method to test the blockchain
    public static void main(String[] args) {
        BCNode1 blockchain = new BCNode1(4); // Difficulty of 4 leading zeros

        System.out.println("Mining block 1...");
        Block1 block1 = new Block1("Transaction Data 1", "");
        blockchain.addBlock(block1);

        System.out.println("Mining block 2...");
        Block1 block2 = new Block1("Transaction Data 2", "");
        blockchain.addBlock(block2);

        System.out.println("Current Blockchain:");
        System.out.println(blockchain);

        // Validate the chain
        System.out.println("Blockchain is valid: " + blockchain.validateChain());
    }
}

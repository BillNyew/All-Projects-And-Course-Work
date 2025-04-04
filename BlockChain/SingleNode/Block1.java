package project2.singlenode;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Date;

public class Block1 {
    private String data;
    private String hash;
    private String previousHash;
    private long timestamp;
    private int nonce;

    // Constructor for the Genesis Block
    public Block1() {
        this.data = "Genesis Block";
        this.timestamp = new Date().getTime();
        this.nonce = 0;
        this.previousHash = "0";  // No previous hash for the first block
        this.hash = calculateBlockHash();
    }

    // Constructor for a new Block
    public Block1(String data, String previousHash) {
        this.data = data;
        this.timestamp = new Date().getTime();
        this.nonce = 0;
        this.previousHash = previousHash;
        this.hash = calculateBlockHash();
    }

    // Calculate the SHA-256 hash of the block
    public String calculateBlockHash() {
        String instanceVarData = previousHash + Long.toString(timestamp) + Integer.toString(nonce) + data;
        return applySHA256(instanceVarData);
    }

    // SHA-256 Hashing function
    private String applySHA256(String input) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hashBytes = digest.digest(input.getBytes("UTF-8"));
            StringBuffer buffer = new StringBuffer();
            for (byte b : hashBytes) {
                buffer.append(String.format("%02x", b));
            }
            return buffer.toString();
        } catch (NoSuchAlgorithmException | java.io.UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }
    }

    // Getters and Setters
    public String getHash() {
        return hash;
    }

    public void setHash(String hash) {
        this.hash = hash;
    }

    public String getPreviousHash() {
        return previousHash;
    }

    public void setPreviousHash(String previousHash) {
        this.previousHash = previousHash;
    }

    public int getNonce() {
        return nonce;
    }

    public void setNonce(int nonce) {
        this.nonce = nonce;
    }

    public String getData() {
        return data;
    }

    public long getTimestamp() {
        return timestamp;
    }

    // toString() for easy debugging
    @Override
    public String toString() {
        return "Block{" +
                "data='" + data + '\'' +
                ", hash='" + hash + '\'' +
                ", previousHash='" + previousHash + '\'' +
                ", timestamp=" + timestamp +
                ", nonce=" + nonce +
                '}';
    }
}


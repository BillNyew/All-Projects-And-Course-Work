import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Date;
import java.io.Serializable;

public class Block implements Serializable {
    private static final long serialVersionUID = 1L;
    private String data;
    private String hash;
    private String previousHash;
    private long timestamp;
    private int nonce;

    // Constructor for the Genesis Block
    public Block() {
        this.data = "Genesis Block";
        this.timestamp = new Date().getTime();
        this.nonce = 0;
        this.previousHash = "0"; // No previous hash for the first block
        this.hash = calculateBlockHash();
    }

    // Constructor for a new Block
    public Block(String data) {
        this.data = data;
        this.timestamp = new Date().getTime();
        this.nonce = 0;
        this.previousHash = "";
        this.hash = calculateBlockHash();
    }

    // Calculate the SHA-256 hash of the block
    public String calculateBlockHash() {
        String input = String.format("%s%d%d%s", previousHash, timestamp, nonce, data);
        return applySHA256(input);
    }

    // SHA-256 Hashing function
    private String applySHA256(String input) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hashBytes = digest.digest(input.getBytes("UTF-8"));
            StringBuilder buffer = new StringBuilder();
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

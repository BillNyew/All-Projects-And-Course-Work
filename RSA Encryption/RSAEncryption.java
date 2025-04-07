package RSAProject;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class RSAEncryption {
    private static final int BLOCK_SIZE = 214;

    private static final BigInteger n = new BigInteger(
        "14298181905606428347627867110585917348912683448698978471804729574373779858086632467238799069649901576504916566304536661705268080039971945507404314082440363737497962776748827332482389599283969278800550813823873063435132684378328939822815610184019316982015941901886112691184498349051766454836272673177203307545214590830176163386832720647098168334761696461462847810619080847797532047942838579638498302905904892859844751396170672344434048027879329595548282317278534435515026753427827313841328736451206675985752448738124499752171280428574482710417865608895117382309990899824941382269138221052659161841874082502923516327369"
    );
    private static final BigInteger e = new BigInteger(
        "4176633317755433431678678465889845648936806464054866324801744270342879044357669071538839129364698164188798225568335994640432560988356730693851317935746877161305651215590558294715565265787259928455687779275518989163716278946174842872593308106774329128648241556306020338325508704527416130688489628415582686345635693623358474263275478962412758022516421325101632609820589933809050550757747025490064609998396350574372258369895583579424232259743356143849915773687015194184717679321087404939363733716866682044749344859345372083518644958446399833747002184853693942701921082639972060795990236397154101820908184629901054840663"
    );
    private static final BigInteger d = new BigInteger(
        "14002174790121783527288317630633164782209207260104997127596659484324683118954544207658545438928308614624419863541136955007512796926197426499840625873197484771163080886647676848153799823249517091727012292596320959149870939248303455680519758666308748236028811332568509339757761177088926065655620436927894316342612758396654539591543545516197467073501771253743377392282456643176883428862584939110553805839174462698718516603826745188004031053048627181817201882415757647925188703809521827024454659375537475317917491255570890824686753321650475963802717179884502587047508924109849803332503937781591334750730252315897935894375"
    );

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter plaintext:");
        String plaintext = scanner.nextLine();

        // Encrypt plaintext
        List<BigInteger> encryptedBlocks = encrypt(plaintext);
        System.out.println("Encrypted blocks:");
        for (BigInteger block : encryptedBlocks) {
            System.out.println(block);
        }

        // Decrypt ciphertext
        String decryptedText = decrypt(encryptedBlocks);
        System.out.println("Decrypted text:");
        System.out.println(decryptedText);

        // Verify decryption
        if (plaintext.equals(decryptedText)) {
            System.out.println("Decryption successful and matches the original plaintext.");
        } else {
            System.out.println("Decryption failed or does not match the original plaintext.");
        }

        scanner.close();
    }

    private static List<BigInteger> encrypt(String plaintext) {
        List<BigInteger> blocks = breakIntoBlocks(plaintext);
        List<BigInteger> encryptedBlocks = new ArrayList<>();

        for (BigInteger block : blocks) {
            encryptedBlocks.add(block.modPow(e, n));
        }

        return encryptedBlocks;
    }

    private static String decrypt(List<BigInteger> encryptedBlocks) {
        StringBuilder decryptedText = new StringBuilder();

        for (BigInteger encryptedBlock : encryptedBlocks) {
            BigInteger decryptedBlock = encryptedBlock.modPow(d, n);
            decryptedText.append(new String(decryptedBlock.toByteArray()));
        }

        return decryptedText.toString();
    }

    private static List<BigInteger> breakIntoBlocks(String text) {
        List<BigInteger> blocks = new ArrayList<>();

        for (int i = 0; i < text.length(); i += BLOCK_SIZE) {
            int end = Math.min(text.length(), i + BLOCK_SIZE);
            String blockString = text.substring(i, end);
            BigInteger block = new BigInteger(1, blockString.getBytes());
            blocks.add(block);
        }

        return blocks;
    }
}

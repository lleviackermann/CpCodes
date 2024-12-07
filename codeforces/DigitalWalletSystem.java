import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

class TransactionException extends Exception {
    private final String errorCode;

    public TransactionException(String errorMessage, String errorCode) {
        super(errorMessage);
        this.errorCode = errorCode;
    }

    public String getErrorCode() {
        return this.errorCode;
    }
}

class DigitalWallet {
    private final String walletId;
    private final String userName;
    private final String userAccessToken;
    private int walletBalance;

    // Constructor without access token
    public DigitalWallet(String walletId, String userName) {
        this(walletId, userName, null);
    }

    // Constructor with access token
    public DigitalWallet(String walletId, String userName, String userAccessToken) {
        this.walletId = walletId;
        this.userName = userName;
        this.userAccessToken = userAccessToken;
        this.walletBalance = 0;
    }

    public String getWalletId() {
        return walletId;
    }

    public String getUsername() {
        return userName;
    }

    public String getUserAccessToken() {
        return userAccessToken;
    }

    public int getWalletBalance() {
        return walletBalance;
    }

    public void setWalletBalance(int walletBalance) {
        this.walletBalance = walletBalance;
    }
}

class DigitalWalletTransaction {
    public void addMoney(DigitalWallet digitalWallet, int amount) throws TransactionException {
        if (digitalWallet.getUserAccessToken() == null) {
            throw new TransactionException("User not authorized.", "USER_NOT_AUTHORIZED");
        }
        if (amount <= 0) {
            throw new TransactionException("Amount should be greater than zero.", "INVALID_AMOUNT");
        }
        digitalWallet.setWalletBalance(digitalWallet.getWalletBalance() + amount);
    }

    public void payMoney(DigitalWallet digitalWallet, int amount) throws TransactionException {
        if (digitalWallet.getUserAccessToken() == null) {
            throw new TransactionException("User not authorized.", "USER_NOT_AUTHORIZED");
        }
        if (amount <= 0) {
            throw new TransactionException("Amount should be greater than zero.", "INVALID_AMOUNT");
        }
        if (digitalWallet.getWalletBalance() < amount) {
            throw new TransactionException("Insufficient balance", "INSUFFICIENT_BALANCE");
        }
        digitalWallet.setWalletBalance(digitalWallet.getWalletBalance() - amount);
    }
}

public class DigitalWalletSystem {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int numberOfWallets = Integer.parseInt(scanner.nextLine());
        Map<String, DigitalWallet> digitalWallets = new HashMap<>();

        // Create wallets
        for (int i = 0; i < numberOfWallets; i++) {
            String[] input = scanner.nextLine().split(" ");
            String walletId = input[0];
            String userName = input[1];
            if (input.length == 2) {
                digitalWallets.put(walletId, new DigitalWallet(walletId, userName));
            } else {
                String accessToken = input[2];
                digitalWallets.put(walletId, new DigitalWallet(walletId, userName, accessToken));
            }
        }

        DigitalWalletTransaction transactionProcessor = new DigitalWalletTransaction();
        int numberOfTransactions = Integer.parseInt(scanner.nextLine());

        // Process transactions
        for (int i = 0; i < numberOfTransactions; i++) {
            String[] transactionInput = scanner.nextLine().split(" ");
            String walletId = transactionInput[0];
            String operation = transactionInput[1];
            int amount = Integer.parseInt(transactionInput[2]);

            DigitalWallet digitalWallet = digitalWallets.get(walletId);
            try {
                if (operation.equals("add")) {
                    transactionProcessor.addMoney(digitalWallet, amount);
                    System.out.println("Wallet successfully credited.");
                } else if (operation.equals("pay")) {
                    transactionProcessor.payMoney(digitalWallet, amount);
                    System.out.println("Wallet successfully debited.");
                }
            } catch (TransactionException e) {
                System.out.println(e.getErrorCode() + ": " + e.getMessage());
            }
        }

        // Print final wallet details
        List<DigitalWallet> sortedWallets = new ArrayList<>(digitalWallets.values());
        sortedWallets.sort(Comparator.comparing(DigitalWallet::getWalletId));

        for (DigitalWallet wallet : sortedWallets) {
            System.out.println(wallet.getWalletId() + " " +
                    wallet.getUsername() + " " +
                    wallet.getWalletBalance());
        }

        scanner.close();
    }
}

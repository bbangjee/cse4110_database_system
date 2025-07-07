-- drop table transaction_product;  
-- drop table inventory;            
-- drop table sales_transaction;    
-- drop table product;              
-- drop table customer;             
-- drop table store;                 
-- drop table vendor;               

CREATE TABLE customer (
    loyalty_ID          VARCHAR(10) NOT NULL,
    name               VARCHAR(20) NOT NULL,
    phone              VARCHAR(11),
    email              VARCHAR(100),
    
    PRIMARY KEY (loyalty_ID)
);

CREATE TABLE vendor (
    vendor_ID          VARCHAR(10) NOT NULL,
    name               VARCHAR(20) NOT NULL,
	phone              VARCHAR(11), 
    email              VARCHAR(100),
    
    PRIMARY KEY (vendor_ID)
);

CREATE TABLE store (
    store_ID           VARCHAR(10) NOT NULL,
    name               VARCHAR(20) NOT NULL,
    address            VARCHAR(200) NOT NULL,
    operating_hours    VARCHAR(50),
    ownership_type     VARCHAR(9) CHECK (ownership_type in ('franchise', 'corporate')) NOT NULL,
    
    PRIMARY KEY (store_ID)
);

CREATE TABLE product (
    UPC                VARCHAR(13) NOT NULL,
    name               VARCHAR(50) NOT NULL,
    brand              VARCHAR(30) NOT NULL,
    package_type       VARCHAR(20),
    size               VARCHAR(10),
    price              numeric(6,2) NOT NULL CHECK (price > 0),
    vendor_ID          VARCHAR(10),
    
    PRIMARY KEY (UPC),

    FOREIGN KEY (vendor_ID) REFERENCES vendor(vendor_ID)
        on delete set null
        on update cascade
);


CREATE TABLE sales_transaction (
    transaction_ID      VARCHAR(13) NOT NULL,
    transaction_date    DATE NOT NULL,
    transaction_time    TIME NOT NULL,
    payment_method 		VARCHAR(4) CHECK (payment_method in ('cash', 'card')) NOT NULL,
    -- total_amount        numeric(8,2) NOT NULL CHECK (total_amount > 0),
    loyalty_ID          VARCHAR(10),
    store_ID            VARCHAR(10) NOT NULL,
    
    PRIMARY KEY (transaction_ID),
    
    FOREIGN KEY (loyalty_ID) REFERENCES customer(loyalty_ID)
        ON DELETE SET NULL
        ON UPDATE CASCADE,
    FOREIGN KEY (store_ID) REFERENCES store(store_ID)
        ON DELETE RESTRICT
        ON UPDATE CASCADE
);

CREATE TABLE inventory (
    store_ID            VARCHAR(10) NOT NULL,
    UPC                 VARCHAR(13) NOT NULL,
    current_quantity    INT CHECK (current_quantity >= 0) NOT NULL,
    reorder_threshold   INT CHECK (reorder_threshold >= 0) NOT NULL,
    reorder_quantity    INT CHECK (reorder_quantity > 0) NOT NULL,
    recent_order_history DATE NOT NULL,
    
    PRIMARY KEY (store_ID, UPC),
    
    FOREIGN KEY (store_ID) REFERENCES store(store_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (UPC) REFERENCES product(UPC)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

CREATE TABLE transaction_product (
    transaction_ID      VARCHAR(13) NOT NULL,
    UPC                 VARCHAR(13) NOT NULL,
    quantity            INT CHECK (quantity > 0) NOT NULL,
    
    PRIMARY KEY (transaction_ID, UPC),

    FOREIGN KEY (transaction_ID) REFERENCES sales_transaction(transaction_ID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (UPC) REFERENCES product(UPC)
        ON DELETE RESTRICT
        ON UPDATE CASCADE
);

FROM php:7.4-apache

# Install necessary tools
RUN apt-get update && apt-get install -y \
    build-essential \
    python3 \
    wget \
    gcc \
    make \
    bc \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Download and install an older version of sudo (e.g., 1.8.27, available in the sudo archives)
RUN wget https://www.sudo.ws/dist/sudo-1.8.27.tar.gz && \
    tar xzf sudo-1.8.27.tar.gz && \
    cd sudo-1.8.27 && \
    ./configure && \
    make && make install && \
    cd .. && rm -rf sudo-1.8.27 sudo-1.8.27.tar.gz

# Add user 'manu' and configure sudo
RUN useradd -m manu && echo "manu:elijah_sougala_acamas_vaudemont" | chpasswd && adduser manu sudo

# Configure sudoers file
RUN echo "www-data ALL=(manu) NOPASSWD: /home/manu/42sh" >> /etc/sudoers && \
    echo "manu ALL=(ALL, !root) NOPASSWD: /usr/bin/vi /home/manu/user.txt" >> /etc/sudoers

# Copy application files
COPY src/ /var/www/html/

# Set permissions
RUN chown -R www-data:www-data /var/www/html && chmod -R 755 /var/www/html

# Add and compile C program
COPY 42sh.c /home/manu/42sh.c
RUN gcc /home/manu/42sh.c -o /home/manu/42sh && \
    chown manu:manu /home/manu/42sh && chmod 4755 /home/manu/42sh && \
    rm -rf /home/manu/42sh.c

# Add user.txt with flag
RUN echo "epictf{elijah_sougala}" > /home/manu/user.txt && \
    chown manu:manu /home/manu/user.txt && chmod 640 /home/manu/user.txt

# Add root.txt with flag
RUN echo "epictf{GGWP_Manu_on_top}" > /root/root.txt && \
    chown root:root /root/root.txt && chmod 600 /root/root.txt

# Expose HTTP port
EXPOSE 80

# Start Apache
CMD ["apache2-foreground"]
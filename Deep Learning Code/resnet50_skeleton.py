import torch.nn as nn

# 1x1 convolution
def conv1x1(in_channels, out_channels, stride, padding):
    model = nn.Sequential(
        nn.Conv2d(in_channels, out_channels, kernel_size=1, stride=stride, padding=padding),
        nn.BatchNorm2d(out_channels),
        nn.ReLU(inplace=True)
    )
    return model


# 3x3 convolution
def conv3x3(in_channels, out_channels, stride, padding):
    model = nn.Sequential(
        nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=stride, padding=padding),
        nn.BatchNorm2d(out_channels),
        nn.ReLU(inplace=True)
    )
    return model

###########################################################################
# Question 1 : Implement the "bottle neck building block" part.
# Hint : Think about difference between downsample True and False. How we make the difference by code?
class ResidualBlock(nn.Module):
    def __init__(self, in_channels, middle_channels, out_channels, downsample=False):
        super(ResidualBlock, self).__init__()
        self.downsample = downsample

        if self.downsample:
            self.layer = nn.Sequential(
                ##########################################
                ############## fill in here 
                # Hint : use these functions (conv1x1, conv3x3)
                conv1x1(in_channels, middle_channels, stride=2, padding=0),  # Downsample with stride=2
                nn.ReLU(inplace=True),
                # Spatial convolution
                conv3x3(middle_channels, middle_channels, stride=1, padding=1),
                nn.ReLU(inplace=True),
                # Expand to out_channels
                conv1x1(middle_channels, out_channels, stride=1, padding=0),
                nn.ReLU(inplace=True)
                #########################################
            )
            self.downsize = conv1x1(in_channels, out_channels, 2, 0)

        else:
            self.layer = nn.Sequential(
                ##########################################
                ############# fill in here 
                conv1x1(in_channels, middle_channels, stride=1, padding=0),
                nn.ReLU(inplace=True),
                # Spatial convolution
                conv3x3(middle_channels, middle_channels, stride=1, padding=1),
                nn.ReLU(inplace=True),
                # Expand to out_channels
                conv1x1(middle_channels, out_channels, stride=1, padding=0),
                nn.ReLU(inplace=True)
                #########################################
            )
            self.make_equal_channel = conv1x1(in_channels, out_channels, 1, 0)

    def forward(self, x):
        if self.downsample:
            out = self.layer(x)
            x = self.downsize(x)
            return out + x
        else:
            out = self.layer(x)
            if x.size() is not out.size():
                x = self.make_equal_channel(x)
            return out + x
###########################################################################



###########################################################################



###########################################################################
# Question 2 : Implement the "class, ResNet50_layer4" part.
# Understand ResNet architecture and fill in the blanks below.
# Implement the code.
class ResNet50_layer4(nn.Module):
    def __init__(self, num_classes=10):  # CIFAR-10 has 10 classes
        super(ResNet50_layer4, self).__init__()

        self.layer1 = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=64, kernel_size=7, stride=1, padding=3),  
            nn.BatchNorm2d(64),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2, padding=1) 
        )

        self.layer2 = nn.Sequential(
            ResidualBlock(in_channels=64, middle_channels=64, out_channels=256, downsample=True),
            ResidualBlock(in_channels=256, middle_channels=64, out_channels=256, downsample=False),
            ResidualBlock(in_channels=256, middle_channels=64, out_channels=256, downsample=False)
        )

        self.layer3 = nn.Sequential(
            ResidualBlock(in_channels=256, middle_channels=128, out_channels=512, downsample=True),
            ResidualBlock(in_channels=512, middle_channels=128, out_channels=512, downsample=False),
            ResidualBlock(in_channels=512, middle_channels=128, out_channels=512, downsample=False),
            ResidualBlock(in_channels=512, middle_channels=128, out_channels=512, downsample=False)
        )

        self.layer4 = nn.Sequential(
            ResidualBlock(in_channels=512, middle_channels=256, out_channels=1024, downsample=True),
            ResidualBlock(in_channels=1024, middle_channels=256, out_channels=1024, downsample=False),
            ResidualBlock(in_channels=1024, middle_channels=256, out_channels=1024, downsample=False),
            ResidualBlock(in_channels=1024, middle_channels=256, out_channels=1024, downsample=False),
            ResidualBlock(in_channels=1024, middle_channels=256, out_channels=1024, downsample=False),
            ResidualBlock(in_channels=1024, middle_channels=256, out_channels=1024, downsample=False)
        )

        self.fc = nn.Linear(1024, num_classes)
        self.avgpool = nn.AvgPool2d(kernel_size=2, stride=2)
        

        for m in self.modules():
            if isinstance(m, nn.Linear):
                nn.init.xavier_uniform_(m.weight.data)
            elif isinstance(m, nn.Conv2d):
                nn.init.xavier_uniform_(m.weight.data)

    def forward(self, x):
        out = self.layer1(x)
        out = self.layer2(out)
        out = self.layer3(out)
        out = self.layer4(out)
        out = self.avgpool(out)
        out = out.view(out.size()[0], -1)
        out = self.fc(out)

        return out
###########################################################################
